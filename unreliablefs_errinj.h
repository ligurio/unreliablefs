#ifndef ERRINJ_HH
#define ERRINJ_HH

#include <signal.h>

#include "unreliablefs_ops.h"

#define MAX_ERRINJ_NAME_LENGTH 20

#if !defined(__OpenBSD__) && !defined(__FreeBSD__) && !defined(__APPLE__)
#define MAX_ERRNO EXFULL
#else
#define MAX_ERRNO ELAST
#endif /* __OpenBSD__ */
#define MIN_ERRNO E2BIG

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
    "errinj_kill_caller",
    "errinj_noop",
};

typedef enum {
    ERRINJ_KILL_CALLER,
    ERRINJ_NOOP,
} errinj_type;

typedef struct errinj_conf errinj_conf;

struct errinj_conf {
    char *err_injection_name;
    char *op_regexp;
    char *path_regexp;
    unsigned int probability;
    errinj_type type;

    TAILQ_ENTRY(errinj_conf) entries;
};

TAILQ_HEAD(err_inj_q, errinj_conf);

#endif /* ERRINJ_HH */
