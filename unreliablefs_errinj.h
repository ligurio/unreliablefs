#ifndef ERRINJ_HH
#define ERRINJ_HH

#include <errno.h>
#include <signal.h>

#include "unreliablefs_ops.h"

#if defined(__linux__)
    #include "unreliablefs_errno_linux.h"
#elif defined(__FreeBSD__)
    #include "unreliablefs_errno_freebsd.h"
#elif defined(__OpenBSD__)
    #include "unreliablefs_errno_openbsd.h"
#elif defined(__APPLE__)
    #include "unreliablefs_errno_macosx.h"
#else
#error Unsupported platform
#endif

#define MAX_ERRINJ_NAME_LENGTH 20
#define MIN_PROBABLITY 0
#define MAX_PROBABLITY 100
#define ERRNO_NOOP -999
#define DEFAULT_SIGNAL_NAME SIGKILL

int error_inject(const char* path, fuse_op operation);
struct err_inj_q *config_init(const char* conf_path);
void config_delete(struct err_inj_q *config);
int conf_option_handler(void* cfg, const char* section,
                        const char* name, const char* value);
int is_regex_matched(const char *regex, const char *string);

const char *errinj_name[] =
{
    "errinj_errno",
    "errinj_kill_caller",
    "errinj_noop",
    "errinj_slowdown",
};

typedef enum {
    ERRINJ_ERRNO,
    ERRINJ_KILL_CALLER,
    ERRINJ_NOOP,
    ERRINJ_SLOWDOWN,
} errinj_type;

typedef struct errinj_conf errinj_conf;

struct errinj_conf {
    char *err_injection_name;
    char *op_regexp;
    char *path_regexp;
    char *errno_regexp;
    unsigned int probability;
    unsigned int duration;
    errinj_type type;

    TAILQ_ENTRY(errinj_conf) entries;
};

TAILQ_HEAD(err_inj_q, errinj_conf);

#endif /* ERRINJ_HH */
