#include "helpers.h"

#include <assert.h>
#include <errno.h>
#include <unistd.h>

#define RW_PERMS 0666

BgProcMgr bg_mgr = {0};

volatile struct {
    char* str_buf;
    int str_len;
    int color_offset;
} sigusr_data = {0};

volatile sig_atomic_t color = 31;

void sigchld_handler(int sig) {
    (void)sig;
    bg_mgr.do_process_reap = true;
}

void sigusr2_handler(int sig) {
    (void)sig;
    
    char* ptr = sigusr_data.str_buf + sigusr_data.color_offset;
    ptr[0] = '0' + (color / 10);
    ptr[1] = '0' + (color % 10);

    color = (color == 36) ? 31 : color + 1;

    write(STDERR_FILENO, sigusr_data.str_buf, sigusr_data.str_len);
}

void init_globals_and_handlers() {
    char* user = getenv("USER");
    if (!user) {
        user = "";
    }

    sigusr_data.str_len = strlen("\x1B[0;") 
                        + 2 
                        + strlen("mHi ") 
                        + strlen(user) 
                        + strlen("!\x1B[0m\n");

    sigusr_data.str_buf = malloc(sigusr_data.str_len + 1);
    sigusr_data.color_offset = strlen("\x1B[0;");
    
    snprintf(
        sigusr_data.str_buf,
        sigusr_data.str_len + 1,
        "\x1B[0;%dmHi %s!\x1B[0m\n",
        color,
        user
    );

    if (signal(SIGSEGV, sigsegv_handler) == SIG_ERR) {
        perror("Failed to set signal handler");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGCHLD, sigchld_handler) == SIG_ERR) {
        perror("Failed to set signal handler");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGUSR2, sigusr2_handler) == SIG_ERR) {
        perror("Failed to set signal handler");
        exit(EXIT_FAILURE);
    }
}

void deinit_globals_and_handlers() {
    signal(SIGSEGV, SIG_DFL);
    signal(SIGCHLD, SIG_DFL);
    signal(SIGUSR2, SIG_DFL);

    bg_mgr_deinit(&bg_mgr);
    validate_input(NULL);
    free(sigusr_data.str_buf);
}

void bg_proc_list_push(BgProcList* list, bgentry_t entry) {
    if (list->size + 1 > list->cap) {
        list->cap = (list->cap == 0) ? 1 : list->cap * 2;
        list->items = realloc(list->items, sizeof(bgentry_t) * list->cap);
    }

    list->items[list->size++] = entry;
}

void bg_proc_list_remove(BgProcList* list, int idx) {
    if (list->size == 0) return;

    for (int i = idx; i < list->size - 1; ++i) {
        list->items[i] = list->items[i + 1];
    }

    --list->size;
}

char* get_cwd_str() {
    int buf_size = 32;
    char* buffer = malloc(buf_size);

    while (getcwd(buffer, buf_size) == NULL) {
        if (errno != ERANGE) return NULL;
        buf_size *= 2;
        buffer = realloc(buffer, buf_size);
    }

    return buffer;
}

void builtin_cd(job_info* job) {
    if (job->procs->argc == 1) {
        char* home = getenv("HOME");
        if (!home) goto failure;
        if (chdir(home) < 0) goto failure;
    } else {
        char* path = job->procs->argv[1];
        if (!path) goto failure;
        if (chdir(path) < 0) goto failure;
    }

    char* cwd = get_cwd_str();
    if (!cwd) goto failure;

    fprintf(stdout, "%s\n", cwd);
    free(cwd);

    return;

failure:
    fprintf(stderr, DIR_ERR);
}

void builtin_fg(BgProcMgr* bg_mgr, job_info* job, int* exit_status) {
    if (bg_mgr->procs.size == 0) {
        fprintf(stdout, PID_ERR);
        return;
    }

    int match_idx = -1;

    if (job->procs->argc == 1) {
        match_idx = 0;
        time_t time = bg_mgr->procs.items[0].seconds;

        for (int i = 1; i < bg_mgr->procs.size; ++i) {
            bgentry_t* entry = &bg_mgr->procs.items[i];

            if (entry->seconds >= time) {
                match_idx = i;
                time = entry->seconds;
            }
        }
    } else {
        pid_t pid;

        if(sscanf(job->procs->argv[1], "%d", &pid) != 1) {
            fprintf(stderr, PID_ERR);
            return;
        }

        for (int i = 0; i < bg_mgr->procs.size; ++i) {
            if (bg_mgr->procs.items[i].pid == pid) {
                match_idx = i;
            }
        }
    }

    if (match_idx == -1) {
        fprintf(stderr, PID_ERR);
        return;
    }

    bgentry_t* match = &bg_mgr->procs.items[match_idx];

    fprintf(stdout, "%s\n", match->job->line);

    int wait_status;
    if (waitpid(match->pid, &wait_status, 0) < 0) {
        printf(WAIT_ERR);
        exit(EXIT_FAILURE);
    }

    if (WIFEXITED(wait_status)) {
        *exit_status = WEXITSTATUS(wait_status);
    }

    free_job(match->job);
    bg_proc_list_remove(&bg_mgr->procs, match_idx);
}

void builtin_bglist(BgProcMgr* bg_mgr) {
    for (int i = 0; i < bg_mgr->procs.size; ++i) {
        print_bgentry(&bg_mgr->procs.items[i]);
    }
}

bool verify_job(job_info* job) {
    if (
        job->in_file && 
        job->out_file && 
        strcmp(job->in_file, job->out_file) == 0
    ) {
        goto job_error;
    }

    bool is_piped = (job->nproc > 1);

    for (proc_info* p = job->procs; p != NULL; p = p->next_proc) {
        // Disallow &> from being used with > or 2>
        if (job->outerr && (job->out_file || is_piped)) {
            goto job_error;
        }

        // Disallow error direction to already used file
        if (
            p->err_file && (
                (job->in_file && strcmp(p->err_file, job->in_file) == 0) || 
                (job->out_file && strcmp(p->err_file, job->out_file) == 0)
            )
        ) {
            goto job_error;
        }
    }

job_ok:
    return true;

job_error:
    fprintf(stderr, RD_ERR);
    return false;
}

typedef struct {
    pid_t last_pid; // Equals the pid of the first child process
    bool success;
} SpawnInfo;

SpawnInfo spawn_job(job_info* job) {
    assert(job->nproc > 0);

    int proc_count = job->nproc;
    int pipe_count = proc_count - 1;
    int (*pipes)[2] = NULL;

    if (pipe_count > 0) {
        pipes = malloc(pipe_count * sizeof(int[2]));
    }

    pid_t last_pid = 0;

    for (int i = 0; i < pipe_count; ++i) {
        if (pipe(pipes[i]) < 0) {
            perror("pipe");
            exit(EXIT_FAILURE);
        };
    }

    proc_info* current_proc = job->procs;

    int in_fd = -1;
    int out_fd = -1;

    // Redirect input file to stdin
    if (job->in_file)  {
        in_fd = open(job->in_file, O_RDONLY, RW_PERMS);

        if (in_fd < 0) {
            fprintf(stderr, RD_ERR);

            return (SpawnInfo){
                .success = false
            };
        }
    }

    if (job->out_file) {
        if (job->append) {
            out_fd = open(job->out_file, O_CREAT | O_WRONLY | O_APPEND, RW_PERMS);
        } else {
            out_fd = open(job->out_file, O_CREAT | O_WRONLY | O_TRUNC, RW_PERMS);
        }
    }

    for (int i = 0; i < proc_count; ++i) {
        pid_t pid;

        if ((pid = fork()) < 0) {
            perror("Fork error");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) { // Child
            // Attach input to stdin
            if (i == 0 && in_fd >= 0) {
                if (dup2(in_fd, STDIN_FILENO) < 0) goto child_err;
                if (close(in_fd)) goto child_err;
            }

            // Attach previous commands stdout to stdin
            if (pipes && i > 0) {
                if (dup2(pipes[i - 1][0], STDIN_FILENO) < 0) goto child_err;
            }

            // Attach stdout to the next stdin
            if (pipes && i < proc_count - 1) {
                if (dup2(pipes[i][1], STDOUT_FILENO) < 0) goto child_err;
            }

            // Redirect stdout to output file
            if (i == proc_count - 1 && out_fd >= 0) {
                if (dup2(out_fd, STDOUT_FILENO) < 0) goto child_err;
                if (close(out_fd)) goto child_err;
            }

            // Redirect stderr
            if (current_proc->err_file) {
                int err_fd = open(current_proc->err_file, O_CREAT | O_TRUNC | O_WRONLY, RW_PERMS);

                if (err_fd < 0) goto child_err;
                if (dup2(err_fd, STDERR_FILENO) < 0) goto child_err;
                if (close(err_fd)) goto child_err;
            }

            for (int j = 0; j < pipe_count; j++) {
                if (close(pipes[j][0])) goto child_err;
                if (close(pipes[j][1])) goto child_err;
            }

            execvp(current_proc->cmd, current_proc->argv);
            printf(EXEC_ERR, current_proc->cmd);

child_err:
            perror("Child encountered error");
            free_job(job);
            deinit_globals_and_handlers();
            exit(EXIT_FAILURE);
        } else if (pid > 0) { // Parent
            // If last child in chain, store pid
            if (i == proc_count - 1) {
                last_pid = pid;
            }

            current_proc = current_proc->next_proc;
        } else {
            perror("fork");
            exit(EXIT_FAILURE);
        }
    }

    if (in_fd >= 0) {
        close(in_fd);
    }

    if (out_fd >= 0) {
        close(out_fd);
    }

    for (int i = 0; i < pipe_count; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    free(pipes);

    return (SpawnInfo){
        .last_pid = last_pid,
        .success = true
    };
}

void run_fg_process(job_info* job, int* exit_status) {
    SpawnInfo info = spawn_job(job);
    if (!info.success) { return; }

    int wait_status;

    if (waitpid(info.last_pid, &wait_status, 0) < 0) {
        printf(WAIT_ERR);
        exit(EXIT_FAILURE);
    }

    if (WIFEXITED(wait_status)) {
        *exit_status = WEXITSTATUS(wait_status);
    }
}

void run_bg_process(BgProcMgr* bg_mgr, job_info* job) {
    SpawnInfo info = spawn_job(job);
    if (!info.success) { return; }

    bg_proc_list_push(&bg_mgr->procs, (bgentry_t){
        .pid = info.last_pid,
        .job = job,
        .seconds = time(NULL)
    });
}

void bg_mgr_deinit(BgProcMgr* bg_mgr) {
    int dummy;
    kill_bg_processes(bg_mgr, &dummy);
    free(bg_mgr->procs.items);
    *bg_mgr = (BgProcMgr){0};
}

void reap_bg_processes(BgProcMgr *bg_mgr, int* exit_status) {
    sigset_t oldmask, blockmask;    

    // NOTE(eli): We block SIGCHLD since we modify bg_mgr->do_process_reap
    sigemptyset(&blockmask);
    sigaddset(&blockmask, SIGCHLD);
    sigprocmask(SIG_BLOCK, &blockmask, &oldmask);

    int status;
    pid_t pid_result;

    while ((pid_result = waitpid(-1, &status, WNOHANG)) > 0) {
        for (int i = bg_mgr->procs.size - 1; i >= 0; --i) {
            bgentry_t* entry = &bg_mgr->procs.items[i];

            if (pid_result == entry->pid) {
                fprintf(stdout, BG_TERM, entry->pid, entry->job->line);
                free_job(entry->job);
                bg_proc_list_remove(&bg_mgr->procs, i);
                break;
            }
        }
    }

    bg_mgr->do_process_reap = false;

    sigprocmask(SIG_SETMASK, &oldmask, NULL);
}

void kill_bg_processes(BgProcMgr *bg_mgr, int* exit_status) {
    for (int i = 0; i < bg_mgr->procs.size; ++i) {
        bgentry_t* entry = &bg_mgr->procs.items[i];

        // TODO(eli): Error checking?
        kill(entry->pid, SIGKILL);
    }

    reap_bg_processes(bg_mgr, exit_status);
}
