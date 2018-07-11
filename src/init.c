
#include <stdlib.h>

#include "ps-internal.h"
#include "common.h"

static const R_CallMethodDef callMethods[]  = {
  /* System api */
  { "ps__os_type",       (DL_FUNC) ps__os_type,       0 },
  { "ps__pids",          (DL_FUNC) ps__pids,          0 },

  /* ps_handle API */
  { "psll_pid",          (DL_FUNC) psll_pid,          1 },
  { "psll_handle",       (DL_FUNC) psll_handle,       2 },
  { "psll_format",       (DL_FUNC) psll_format,       1 },
  { "psll_parent",       (DL_FUNC) psll_parent,       1 },
  { "psll_ppid",         (DL_FUNC) psll_ppid,         1 },
  { "psll_is_running",   (DL_FUNC) psll_is_running,   1 },
  { "psll_name",         (DL_FUNC) psll_name,         1 },
  { "psll_exe",          (DL_FUNC) psll_exe,          1 },
  { "psll_cmdline",      (DL_FUNC) psll_cmdline,      1 },
  { "psll_status",       (DL_FUNC) psll_status,       1 },
  { "psll_username",     (DL_FUNC) psll_username,     1 },
  { "psll_create_time",  (DL_FUNC) psll_create_time,  1 },
  { "psll_cwd",          (DL_FUNC) psll_cwd,          1 },
  { "psll_uids",         (DL_FUNC) psll_uids,         1 },
  { "psll_gids",         (DL_FUNC) psll_gids,         1 },
  { "psll_terminal",     (DL_FUNC) psll_terminal,     1 },
  { "psll_environ",      (DL_FUNC) psll_environ,      1 },
  { "psll_num_threads",  (DL_FUNC) psll_num_threads , 1 },
  { "psll_cpu_times",    (DL_FUNC) psll_cpu_times,    1 },
  { "psll_memory_info",  (DL_FUNC) psll_memory_info , 1 },
  { "psll_send_signal",  (DL_FUNC) psll_send_signal , 2 },
  { "psll_suspend",      (DL_FUNC) psll_suspend,      1 },
  { "psll_resume",       (DL_FUNC) psll_resume,       1 },
  { "psll_terminate",    (DL_FUNC) psll_terminate,    1 },
  { "psll_kill",         (DL_FUNC) psll_kill,         1 },

  /* Utils */
  { "ps__init",          (DL_FUNC) ps__init,          2 },

  { "psp__pid_exists",   (DL_FUNC) psp__pid_exists,   1 },
  { "psp__stat_st_rdev", (DL_FUNC) psp__stat_st_rdev, 1 },
  { "psp__zombie",       (DL_FUNC) psp__zombie,       0 },
  { "psp__waitpid",      (DL_FUNC) psp__waitpid,      1 },

  { NULL, NULL, 0 }
};

/*
 * Called on module import on all platforms.
 */
void R_init_ps(DllInfo *dll) {
  if (getenv("R_PS_DEBUG") != NULL) PS__DEBUG = 1;
  if (getenv("R_PS_TESTING") != NULL) PS__TESTING = 1;

  PROTECT(ps__last_error = ps__build_named_list(
    "ssii",
    "message", "Unknown error",
    "class", "fs_error",
    "errno", 0,
    "pid", NA_INTEGER
  ));

  R_PreserveObject(ps__last_error);
  UNPROTECT(1);

  R_registerRoutines(dll, NULL, callMethods, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
  R_forceSymbols(dll, TRUE);
}