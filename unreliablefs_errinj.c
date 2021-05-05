#define FUSE_USE_VERSION 29

#include <fuse.h>
#include <libgen.h> /* basename() and dirname() */
#include <regex.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/queue.h>

#include "conf.h"
#include "unreliablefs.h"
#include "unreliablefs_errinj.h"

static int rand_range(int min_n, int max_n)
{
    return rand() % (max_n - min_n + 1) + min_n;
}

int error_inject(const char* path, char* operation)
{
    int rc = -0;
    struct errinj_conf *err;
    /* read configuration file on change */
    pthread_mutex_lock(&conf.mutex);
    if (strcmp(path, conf.config_path) == 0) {
        config_delete(conf.errors);
        conf.errors = config_init(path);
    }
    if (!conf.errors) {
        goto cleanup;
    }

    /* apply error injections defined in configuration one by one */
    TAILQ_FOREACH(err, conf.errors, entries) {
	if (is_regex_matched(err->path_regexp, path) != 0) {
	    fprintf(stderr, "errinj '%s' skipped: path_regexp (%s) is not matched\n",
                            errinj_name[err->type], err->path_regexp);
	    continue;
	}
	if (is_regex_matched(err->op_regexp, operation) != 0) {
	    fprintf(stderr, "errinj '%s' skipped: op_regexp (%s) is not matched\n",
                            errinj_name[err->type], err->op_regexp);
	    continue;
	}
        int p = rand_range(MIN_PROBABLITY, MAX_PROBABLITY);
        if (!((p >= 0) && (p <= err->probability))) {
            fprintf(stderr, "errinj '%s' skipped: probability (%d) is not matched\n",
                            errinj_name[err->type], err->probability);
            continue;
        }
	switch (err->type) {
        case ERRINJ_NOOP:
            fprintf(stderr, "%s triggered on operation '%s', %s\n",
                            errinj_name[err->type], operation, path);
            rc = -ERRNO_NOOP;
            break;
        }
    }

cleanup:
    pthread_mutex_unlock(&conf.mutex);
    return rc;
}

static errinj_type errinj_type_by_name(const char *name)
{
    int idx = 0;
    int n_elem = sizeof(errinj_name)/sizeof(errinj_name[0]);
    for (int i = 0; i < n_elem; i++) {
        if (strcmp(errinj_name[i], name) == 0)
            idx = i;
    }

    return (errinj_type)idx;
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
    errinj_type cur_type = errinj_type_by_name(section);
    errinj_conf *np;
    int is_errinj_found = 0;
    TAILQ_FOREACH(np, (struct err_inj_q *)cfg, entries) {
        if (np->type == cur_type) {
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
    int rc = regcomp(&reg, regex, REG_ICASE | REG_EXTENDED);
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
