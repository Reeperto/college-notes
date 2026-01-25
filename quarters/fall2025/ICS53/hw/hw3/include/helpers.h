#include "icssh.h"

bool verify_job(job_info* job);

typedef struct {
    int size, cap;
    bgentry_t* items;
} BgProcList;

typedef struct {
    BgProcList procs;
    volatile bool do_process_reap;
} BgProcMgr;

void bg_mgr_deinit(BgProcMgr* bg_mgr);

void run_fg_process(job_info* job, int* exit_status);
void run_bg_process(BgProcMgr* bg_mgr, job_info* job);

void reap_bg_processes(BgProcMgr *bg_mgr, int* exit_code);
void kill_bg_processes(BgProcMgr *bg_mgr, int* exit_code);

void builtin_cd(job_info* job);
void builtin_bglist(BgProcMgr* bg_mgr);
void builtin_fg(BgProcMgr* bg_mgr, job_info* job, int* exit_status);

// Globals
extern BgProcMgr bg_mgr;

void init_globals_and_handlers();
void deinit_globals_and_handlers();
