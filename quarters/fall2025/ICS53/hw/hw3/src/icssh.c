#include "icssh.h"

#include <assert.h>
#include <readline/readline.h>

#include "helpers.h"

int main(int argc, char* argv[]) {
    init_globals_and_handlers();

    int max_bgprocs = -1;
    int exit_status = 0;
    char* line = NULL;

#ifdef GS
    rl_outstream = fopen("/dev/null", "w");
#endif

    int max_bg_procs = -1;

    if(argc > 1) {
        int check = atoi(argv[1]);
        if(check != 0)
            max_bg_procs = check;
        else {
            printf("Invalid command line argument value\n");
            exit(EXIT_FAILURE);
        }
    }

    job_info* job;
    while ((line = readline(SHELL_PROMPT)) != NULL) {
        job = validate_input(line);

        if (job == NULL) {
            goto next_cmd;
        } else if (!verify_job(job)) {
            goto next_and_free_job;
        }

        if (bg_mgr.do_process_reap) {
            reap_bg_processes(&bg_mgr, &exit_status);
        }

#ifdef DEBUG
        debug_print_job(job);
#endif

        if (strcmp(job->procs->cmd, "exit") == 0) {
            kill_bg_processes(&bg_mgr, &exit_status);
            goto exit_shell;
        } else if (strcmp(job->procs->cmd, "estatus") == 0) {
            fprintf(stdout, "%d\n", exit_status);
            goto next_and_free_job;
        } else if (strcmp(job->procs->cmd, "cd") == 0) {
            builtin_cd(job);
            goto next_and_free_job;
        } else if (strcmp(job->procs->cmd, "bglist") == 0) {
            builtin_bglist(&bg_mgr);
            goto next_and_free_job;
        } else if (strcmp(job->procs->cmd, "fg") == 0) {
            builtin_fg(&bg_mgr, job, &exit_status);
            goto next_and_free_job;
        }

        if (!job->bg) {
            run_fg_process(job, &exit_status);
            goto next_and_free_job;
        } else {
            if (max_bg_procs != -1 && max_bg_procs <= bg_mgr.procs.size) {
                fprintf(stderr, BG_ERR);
                goto next_and_free_job;
            }

            run_bg_process(&bg_mgr, job);
            goto next_cmd;
        }

next_and_free_job:
        free_job(job);
        job = NULL;

next_cmd:
        free(line);
        line = NULL;
    }

exit_shell:
    free(line);
    free_job(job);
    deinit_globals_and_handlers();

#ifndef GS
    fclose(rl_outstream);
#endif

    return 0;
}
