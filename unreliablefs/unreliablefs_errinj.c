#define FUSE_USE_VERSION 29

#include <fuse.h>
#include <libgen.h> /* basename() and dirname() */
#include <regex.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/queue.h>

#include "conf.h"
#include "unreliablefs.h"
#include "unreliablefs_errinj.h"

static int rand_range(int, int);
int error_inject(const char* path, fuse_op operation);

extern struct unreliablefs_config conf;

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

#define RANDOM_ELEMENT(arr) \
        (arr[rand_range(0, ARRAY_SIZE(arr))]);

static int op_random_errno(int op_n)
{
    int rc = -1;
    switch (op_n) {
    case OP_LSTAT:
        rc = RANDOM_ELEMENT(errno_lstat);
        break;
    case OP_GETATTR:
        rc = RANDOM_ELEMENT(errno_lstat);
        break;
    case OP_READLINK:
        rc = RANDOM_ELEMENT(errno_readlink);
        break;
    case OP_MKNOD:
        rc = RANDOM_ELEMENT(errno_mknod);
        break;
    case OP_MKDIR:
        rc = RANDOM_ELEMENT(errno_mkdir);
        break;
    case OP_UNLINK:
        rc = RANDOM_ELEMENT(errno_unlink);
        break;
    case OP_RMDIR:
        rc = RANDOM_ELEMENT(errno_rmdir);
        break;
    case OP_SYMLINK:
        rc = RANDOM_ELEMENT(errno_symlink);
        break;
    case OP_RENAME:
        rc = RANDOM_ELEMENT(errno_rename);
        break;
    case OP_LINK:
        rc = RANDOM_ELEMENT(errno_link);
        break;
    case OP_CHMOD:
        rc = RANDOM_ELEMENT(errno_chmod);
        break;
    case OP_CHOWN:
        rc = RANDOM_ELEMENT(errno_chmod);
        break;
    case OP_TRUNCATE:
        rc = RANDOM_ELEMENT(errno_truncate);
        break;
    case OP_OPEN:
        rc = RANDOM_ELEMENT(errno_creat);
        break;
    case OP_READ:
        rc = RANDOM_ELEMENT(errno_read);
        break;
    case OP_WRITE:
        rc = RANDOM_ELEMENT(errno_write);
        break;
    case OP_STATFS:
        rc = RANDOM_ELEMENT(errno_statfs);
        break;
    case OP_FLUSH:
        rc = RANDOM_ELEMENT(errno_close);
        break;
    case OP_RELEASE:
        rc = RANDOM_ELEMENT(errno_close);
        break;
    case OP_FSYNC:
        rc = RANDOM_ELEMENT(errno_fsync);
        break;
#ifdef HAVE_XATTR
    case OP_SETXATTR:
        rc = RANDOM_ELEMENT(errno_setxattr);
        break;
    case OP_GETXATTR:
        rc = RANDOM_ELEMENT(errno_getxattr);
        break;
    case OP_LISTXATTR:
        rc = RANDOM_ELEMENT(errno_listxattr);
        break;
    case OP_REMOVEXATTR:
        rc = RANDOM_ELEMENT(errno_removexattr);
        break;
#endif /* HAVE_XATTR */
    case OP_OPENDIR:
        rc = RANDOM_ELEMENT(errno_opendir);
        break;
    case OP_READDIR:
        rc = RANDOM_ELEMENT(errno_readdir);
        break;
    case OP_RELEASEDIR:
        rc = RANDOM_ELEMENT(errno_close);
        break;
    case OP_FSYNCDIR:
        rc = RANDOM_ELEMENT(errno_fsync);
        break;
    case OP_ACCESS:
        rc = RANDOM_ELEMENT(errno_access);
        break;
    case OP_CREAT:
        rc = RANDOM_ELEMENT(errno_creat);
        break;
    case OP_FTRUNCATE:
        rc = RANDOM_ELEMENT(errno_ftruncate);
        break;
    case OP_FGETATTR:
        rc = RANDOM_ELEMENT(errno_lstat);
        break;
    case OP_LOCK:
        rc = RANDOM_ELEMENT(errno_fcntl);
        break;
#if !defined(__OpenBSD__)
    case OP_IOCTL:
        rc = RANDOM_ELEMENT(errno_ioctl);
        break;
#endif /* __OpenBSD__ */
#ifdef HAVE_FLOCK
    case OP_FLOCK:
        rc = RANDOM_ELEMENT(errno_flock);
        break;
#endif /* HAVE_FLOCK */
#ifdef HAVE_FALLOCATE
    case OP_FALLOCATE:
        rc = RANDOM_ELEMENT(errno_fallocate);
        break;
#endif /* HAVE_FALLOCATE */
#ifdef HAVE_UTIMENSAT
    case OP_UTIMENS:
        rc = RANDOM_ELEMENT(errno_utimensat);
        break;
#endif /* HAVE_UTIMENSAT */
    default:
        fprintf(stderr, "Unsupported operation (%s)\n", fuse_op_name[op_n]);
    }

    return rc;
}

static int rand_range(int min_n, int max_n)
{
    return rand() % (max_n - min_n + 1) + min_n;
}

int error_inject(const char* path, fuse_op operation)
{
    /* instead of returning an error in 'errno', the operation should return
     * the negated error value (-errno) directly.
     */
    int rc = -0;
    struct errinj_conf *err;
    /* read configuration file on change */
    pthread_mutex_lock(&conf.mutex);
    if (strcmp(path, conf.config_path) == 0) {
        config_delete(conf.errors);
        conf.errors = config_init(path);
        goto cleanup;
    }
    if (!conf.errors) {
        goto cleanup;
    }

    /* apply error injections defined in configuration one by one */
    TAILQ_FOREACH(err, conf.errors, entries) {
        unsigned int p = rand_range(MIN_PROBABLITY, MAX_PROBABLITY);
        if (!(p <= err->probability)) {
            fprintf(stderr, "errinj '%s' skipped: probability (%d) is not matched\n",
                            errinj_name[err->type], err->probability);
            continue;
        }
        const char* op_name = fuse_op_name[operation];
	if (is_regex_matched(err->path_regexp, path) != 0) {
	    fprintf(stderr, "errinj '%s' skipped: path_regexp (%s) is not matched\n",
                            errinj_name[err->type], err->path_regexp);
	    continue;
	}
	if (is_regex_matched(err->op_regexp, op_name) != 0) {
	    fprintf(stderr, "errinj '%s' skipped: op_regexp (%s) is not matched\n",
                            errinj_name[err->type], err->op_regexp);
	    continue;
	}
        fprintf(stdout, "%s triggered on operation '%s', %s\n",
                        errinj_name[err->type], op_name, path);
	switch (err->type) {
        case ERRINJ_NOOP:
            rc = -ERRNO_NOOP;
            break;
        case ERRINJ_KILL_CALLER: ;
            struct fuse_context *cxt = fuse_get_context();
            if (cxt) {
                int ret = kill(cxt->pid, DEFAULT_SIGNAL_NAME);
                if (ret == -1) {
                    perror("kill");
                }
                fprintf(stdout, "send signal %s to TID %d\n",
                                strsignal(DEFAULT_SIGNAL_NAME), cxt->pid);
            }
            break;
        case ERRINJ_ERRNO:
            rc = op_random_errno(operation);
            fprintf(stdout, "errno '%s'\n", strerror(rc));
            rc = -rc;
            break;
        case ERRINJ_SLOWDOWN: ;
	    struct timespec ts = {};
	    ts.tv_nsec = err->duration;
            fprintf(stdout, "start of '%s' slowdown for '%d' ns\n", op_name, err->duration);
            if (nanosleep(&ts, NULL) != 0) {
		perror("nanosleep");
            } else {
		fprintf(stdout, "end of '%s' slowdown with '%d' ns\n", op_name, err->duration);
            }
            break;
        }
    }

cleanup:
    pthread_mutex_unlock(&conf.mutex);
    return rc;
}

static errinj_type errinj_type_by_name(const char *name)
{
    int idx = -1;
    int n_elem = sizeof(errinj_name)/sizeof(errinj_name[0]);
    for (int i = 0; i < n_elem; i++) {
        if (strcmp(errinj_name[i], name) == 0)
            idx = i;
    }

    return idx;
}

struct err_inj_q *config_init(const char* conf_path) {
    fprintf(stdout, "read configuration %s\n", conf_path);
    struct err_inj_q *errors = calloc(1, sizeof(struct err_inj_q));
    if (!errors) {
        perror("calloc");
        return NULL;
    }
    TAILQ_INIT(errors);  /* initialize queue */
    if (access(conf_path, F_OK ) == 0) {
        if (ini_parse(conf_path, conf_option_handler, errors) < 0) {
            fprintf(stderr, "can't load '%s'\n", conf_path);
            return NULL;
        }
    }

    return errors;
}

void config_delete(struct err_inj_q *errors) {
    if (!errors) {
        return;
    }
    errinj_conf *err;
    /* delete configuration of error injections */
    while ((err= TAILQ_FIRST(errors))) {
        if (err->path_regexp)
	    free((char*)err->path_regexp);
        if (err->op_regexp)
	    free((char*)err->op_regexp);
	TAILQ_REMOVE(errors, err, entries);
	free(err);
    }
    free(errors);
}

int conf_option_handler(void* cfg, const char* section,
                        const char* key, const char* value)
{
    errinj_conf *err = NULL;
    int cur_type = errinj_type_by_name(section);
    if (cur_type == -1) {
        fprintf(stderr, "unsupported error injection type '%s'", section);
        return -1;
    }
    errinj_conf *np;
    int is_errinj_found = 0;
    TAILQ_FOREACH(np, (struct err_inj_q *)cfg, entries) {
        if (np->type == (errinj_type)cur_type) {
            err = np;
            is_errinj_found = 1;
            break;
        }
    }
    if (!err) {
        if ((err = calloc(1, sizeof(struct errinj_conf))) == NULL) {
            perror("calloc");
            return -1;
        }
        err->type = cur_type;
    }

    if (is_errinj_found != 1) {
        TAILQ_INSERT_TAIL((struct err_inj_q *)cfg, err, entries);
        fprintf(stdout, "enabled error injection %s\n", section);
    }
    fprintf(stdout, "[%s] %s = %s\n", section, key, value);
    if (strcmp(key, "path_regexp") == 0) {
        if (err->path_regexp)
            free(err->path_regexp);
        err->path_regexp = strdup(value);
    } else if (strcmp(key, "op_regexp") == 0) {
        if (err->op_regexp)
            free(err->op_regexp);
        err->op_regexp = strdup(value);
    } else if (strcmp(key, "probability") == 0) {
        err->probability = atoi(value);
    } else if (strcmp(key, "duration") == 0) {
        err->duration = atoi(value);
    } else {
        fprintf(stderr, "unknown option '%s' in configuration file\n", key);
        return 0;
    }

    return 1;
}

int is_regex_matched(const char *regex, const char *string) {
    if (!regex || !string)
        return 0;
    regex_t reg;
    regmatch_t match[1];
    int rc = 0;
    rc = regcomp(&reg, regex, REG_ICASE | REG_EXTENDED);
    if (rc != 0) {
        perror("regcomp");
        regfree(&reg);
        return rc;
    }
    rc = regexec(&reg, string, 1, match, 0);
    if (rc != 0) {
        perror("regexec");
    }
    regfree(&reg);
    return rc;
}
