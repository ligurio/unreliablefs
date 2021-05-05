#ifndef ERRINJ_HH
#define ERRINJ_HH

#include <errno.h>
#include <signal.h>

#include "unreliablefs_ops.h"

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
};

typedef enum {
    ERRINJ_ERRNO,
    ERRINJ_KILL_CALLER,
    ERRINJ_NOOP,
} errinj_type;

typedef struct errinj_conf errinj_conf;

struct errinj_conf {
    char *err_injection_name;
    char *op_regexp;
    char *path_regexp;
    char *errno_regexp;
    unsigned int probability;
    errinj_type type;

    TAILQ_ENTRY(errinj_conf) entries;
};

TAILQ_HEAD(err_inj_q, errinj_conf);

static const int errno_access[] = {
#ifdef __linux__
    EACCES,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
    EROFS,
    EFAULT,
    EINVAL,
    EIO,
    ENOMEM,
    ETXTBSY,
#endif /* __linux__ */

#ifdef __FreeBSD__
    EACCES,
    EFAULT,
    EINTEGRITY,
    EINVAL,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
    EROFS,
    ETXTBSY,
#endif /* __FreeBSD__ */

#ifdef __OpenBSD__
#endif /* __OpenBSD__ */
};

static const int errno_chmod[] = {
#ifdef __linux__
    EACCES,
    EFAULT,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOTDIR,
    EPERM,
    EROFS,
#endif /* __linux__ */

#ifdef __FreeBSD__
    EACCES,
    EFAULT,
    EFTYPE,
    EINTEGRITY,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
    EPERM,
    EPERM,
    EROFS,
#endif /* __FreeBSD__ */

#ifdef __OpenBSD__
#endif /* __OpenBSD__ */
};

static const int errno_creat[] = {
#ifdef __linux__
    EACCES,
    EDQUOT,
    EEXIST,
    EFAULT,
    EFBIG,
    EINTR,
    EINVAL,
    EISDIR,
    ELOOP,
    EMFILE,
    ENAMETOOLONG,
    ENFILE,
    ENODEV,
    ENOENT,
    ENOMEM,
    ENOSPC,
    ENOTDIR,
    ENXIO,
    EOPNOTSUPP,
    EOVERFLOW,
    EPERM,
    EROFS,
    ETXTBSY,
    EWOULDBLOCK,
#endif /* __linux__ */

#ifdef __FreeBSD__
#endif /* __FreeBSD__ */

#ifdef __OpenBSD__
#endif /* __OpenBSD__ */
};

static const int errno_ftruncate[] = {
#ifdef __linux__
    EACCES,
    EBADF,
    EFAULT,
    EFBIG,
    EINTR,
    EINVAL,
    EIO,
    EISDIR,
    ELOOP,
    ENAMETOOLONG,
    ENOTDIR,
    EPERM,
    EROFS,
    ETXTBSY,
#endif /* __linux__ */

#ifdef __FreeBSD__
    EACCES,
    EBADF,
    EFAULT,
    EFBIG,
    EINTEGRITY,
    EINVAL,
    EIO,
    EISDIR,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
    EPERM,
    EROFS,
    ETXTBSY,
#endif /* __FreeBSD__ */

#ifdef __OpenBSD__
#endif /* __OpenBSD__ */
};

static const int errno_link[] = {
#ifdef __linux__
    EACCES,
    EDQUOT,
    EEXIST,
    EFAULT,
    EIO,
    ELOOP,
    EMLINK,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOSPC,
    ENOTDIR,
    EPERM,
    EROFS,
    EXDEV,
#endif /* __linux__ */

#ifdef __FreeBSD__
    EACCES,
    EBADF,
    EDQUOT,
    EEXIST,
    EFAULT,
    EINTEGRITY,
    EINVAL,
    EIO,
    ELOOP,
    EMLINK,
    ENAMETOOLONG,
    ENOENT,
    ENOSPC,
    ENOTDIR,
    EOPNOTSUPP,
    EPERM,
    EROFS,
    EXDEV,
#endif /* __FreeBSD__ */

#ifdef __OpenBSD__
#endif /* __OpenBSD__ */
};

static const int errno_mkdir[] = {
#ifdef __linux__
    EACCES,
    EDQUOT,
    EEXIST,
    EFAULT,
    EINVAL,
    ELOOP,
    EMLINK,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOSPC,
    ENOTDIR,
    EPERM,
    EROFS,
#endif /* __linux__ */

#ifdef __FreeBSD__
    EACCES,
    EBADF,
    EDQUOT,
    EEXIST,
    EFAULT,
    EINTEGRITY,
    EIO,
    ELOOP,
    EMLINK,
    ENAMETOOLONG,
    ENOENT,
    ENOSPC,
    ENOTDIR,
    EPERM,
    EROFS,
#endif /* __FreeBSD__ */

#ifdef __OpenBSD__
#endif /* __OpenBSD__ */
};

static const int errno_mknod[] = {
#ifdef __linux__
    EACCES,
    EDQUOT,
    EEXIST,
    EFAULT,
    EINVAL,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOSPC,
    ENOTDIR,
    EPERM,
    EROFS ,
#endif /* __linux__ */

#ifdef __FreeBSD__
    EACCES,
    EBADF,
    EDQUOT,
    EEXIST,
    EFAULT,
    EINTEGRITY,
    EINVAL,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOSPC,
    ENOTDIR,
    EPERM,
    EROFS,
#endif /* __FreeBSD__ */

#ifdef __OpenBSD__
#endif /* __OpenBSD__ */
};

static const int errno_opendir[] = {
#ifdef __linux__
    EACCES,
    EBADF,
    EMFILE,
    ENOENT,
    ENOMEM,
    ENOTDIR,
#endif /* __linux__ */

#ifdef __FreeBSD__
	/* FIXME */
#endif /* __FreeBSD__ */

#ifdef __OpenBSD__
#endif /* __OpenBSD__ */
};

static const int errno_readdir[] = {
#ifdef __linux__
    EBADF,
#endif /* __linux__ */

#ifdef __FreeBSD__
	/* FIXME */
#endif /* __FreeBSD__ */

#ifdef __OpenBSD__
#endif /* __OpenBSD__ */
};

static const int errno_read[] = {
#ifdef __linux__
    EAGAIN,
    EWOULDBLOCK,
    EBADF,
    EFAULT,
    EINTR,
    EINVAL,
    EIO,
    EISDIR,
#endif /* __linux__ */

#ifdef __FreeBSD__
    EAGAIN,
    EBADF,
    EBUSY,
    ECONNRESET,
    EFAULT,
    EINTEGRITY,
    EINTR,
    EINVAL,
    EIO,
    EISDIR,
    EOPNOTSUPP,
    EOVERFLOW,
#endif /* __FreeBSD__ */

#ifdef __OpenBSD__
#endif /* __OpenBSD__ */
};

static const int errno_readlink[] = {
#ifdef __linux__
    EACCES,
    EFAULT,
    EINVAL,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOTDIR,
#endif /* __linux__ */

#ifdef __FreeBSD__
    EACCES,
    EFAULT,
    EINTEGRITY,
    EINVAL,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
#endif /* __FreeBSD__ */

#ifdef __OpenBSD__
#endif /* __OpenBSD__ */
};

static const int errno_rename[] = {
#ifdef __linux__
    EACCES,
    EBUSY,
    EDQUOT,
    EEXIST,
    EFAULT,
    EINVAL,
    EISDIR,
    ELOOP,
    EMLINK,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOSPC,
    ENOTDIR,
    ENOTEMPTY,
    EPERM,
    EROFS,
#endif /* __linux__ */

#ifdef __FreeBSD__
    EACCES,
    ECAPMODE,
    EDQUOT,
    EFAULT,
    EINTEGRITY,
    EINVAL,
    EIO,
    EISDIR,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOSPC,
    ENOTDIR,
    ENOTEMPTY,
    EPERM,
    EROFS,
    EXDEV,
#endif /* __FreeBSD__ */

#ifdef __OpenBSD__
#endif /* __OpenBSD__ */
};

static const int errno_rmdir[] = {
#ifdef __linux__
    EACCES,
    EBUSY,
    EFAULT,
    EINVAL,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOTDIR,
    ENOTEMPTY,
    EPERM,
    EROFS,
#endif /* __linux__ */

#ifdef __FreeBSD__
    EACCES,
    EBUSY,
    EFAULT,
    EINTEGRITY,
    EINVAL,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
    ENOTEMPTY,
    EPERM,
    EROFS,
#endif /* __FreeBSD__ */

#ifdef __OpenBSD__
#endif /* __OpenBSD__ */
};

static const int errno_symlink[] = {
#ifdef __linux__
    EACCES,
    EDQUOT,
    EEXIST,
    EFAULT,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOSPC,
    ENOTDIR,
    EPERM,
    EROFS,
#endif /* __linux__ */

#ifdef __FreeBSD__
    EACCES,
    EDQUOT,
    EEXIST,
    EFAULT,
    EINTEGRITY,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOSPC,
    ENOTDIR,
    EPERM,
    EROFS,
#endif /* __FreeBSD__ */

#ifdef __OpenBSD__
#endif /* __OpenBSD__ */
};

static const int errno_truncate[] = {
#ifdef __linux__
    EACCES,
    EFAULT,
    EFBIG,
    EINTR,
    EINVAL,
    EIO,
    EISDIR,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
    EPERM,
    EROFS,
    ETXTBSY,
#endif /* __linux__ */

#ifdef __FreeBSD__
    EACCES,
    EFAULT,
    EFBIG,
    EINTEGRITY,
    EINVAL,
    EIO,
    EISDIR,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
    EPERM,
    EROFS,
    ETXTBSY,
#endif /* __FreeBSD__ */

#ifdef __OpenBSD__
#endif /* __OpenBSD__ */
};

static const int errno_unlink[] = {
#if defined(__linux__)
    EACCES,
    EBUSY,
    EFAULT,
    EIO,
    EISDIR,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOTDIR,
#endif /* __linux__ */

#ifdef __FreeBSD__
    EACCES,
    EFAULT,
    EINTEGRITY,
    EIO,
    EISDIR,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOSPC,
    ENOTDIR,
    EPERM,
    EROFS,
#endif /* __FreeBSD__ */

#ifdef __OpenBSD__
#endif /* __OpenBSD__ */
};

static const int errno_write[] = {
#if defined(__linux__)
    EAGAIN,
    EWOULDBLOCK,
    EBADF,
    EDESTADDRREQ,
    EDQUOT,
    EFAULT,
    EFBIG,
    EINTR,
    EINVAL,
    ENOSPC,
    EPERM,
    EPIPE,
#endif /* __linux__ */

#ifdef __FreeBSD__
    EAGAIN,
    EBADF,
    EDQUOT,
    EFAULT,
    EFBIG,
    EINTEGRITY,
    EINTR,
    EINVAL,
    EIO,
    ENOSPC,
    EPIPE,
    EROFS,
#endif /* __FreeBSD__ */

#ifdef __OpenBSD__
#endif /* __OpenBSD__ */
};

static const int errno_lstat[] = {
#if defined(__linux__)
    EACCES,
    EBADF,
    EFAULT,
    EINVAL,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOTDIR,
    EOVERFLOW,
#endif /* __linux__ */

#ifdef __FreeBSD__
    EACCES,
    EFAULT,
    EINTEGRITY,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
    EOVERFLOW,
#endif /* __FreeBSD__ */

#ifdef __OpenBSD__
#endif /* __OpenBSD__ */
};

static const int errno_statfs[] = {
#ifdef __linux__
    EACCES,
    EFAULT,
    EINTR,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOSYS,
    ENOTDIR,
    EOVERFLOW,
#endif /* __linux__ */

#ifdef __FreeBSD__
    EACCES,
    EFAULT,
    EINTEGRITY,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
#endif /* __FreeBSD__ */

#ifdef __OpenBSD__
    EACCES,
    EFAULT,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
#endif /* __OpenBSD__ */
};

static const int errno_close[] = {
#ifdef __linux__
    EBADF,
    EDQUOT,
    EINTR,
    EIO,
    ENOSPC,
#endif /* __linux__ */

#ifdef __FreeBSD__
    EBADF,
    EINTR,
    ENOSPC,
    ECONNRESET,
#endif /* __FreeBSD__ */

#ifdef __OpenBSD__
    EBADF,
    EINTR,
    EIO,
#endif /* __OpenBSD__ */
};

static const int errno_utimensat[] = {
#ifdef __linux__
    EACCES,
    EBADF,
    EFAULT,
    EINVAL,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
    EPERM,
    EROFS,
    ESRCH,
#endif /* __linux__ */

#ifdef __FreeBSD__
    EACCES,
    EBADF,
    EFAULT,
    EINTEGRITY,
    EINVAL,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
    EPERM,
    EROFS,
    ESRCH,
#endif /* __FreeBSD__ */
};

static const int errno_fsync[] = {
#ifdef __linux__
    EBADF,
    EDQUOT,
    EINVAL,
    EIO,
    ENOSPC,
    EROFS,
#endif /* __linux__ */

#ifdef __FreeBSD__
    EBADF,
    EINTEGRITY,
    EINVAL,
    EIO,
#endif /* __FreeBSD__ */
};

static const int errno_setxattr[] = {
#ifdef __linux__
    EDQUOT,
    EEXIST,
    ENODATA,
    ENOSPC,
    ENOTSUP,
    EPERM,
    ERANGE,
    /* In addition, the errors documented in stat(2) can also occur. */
    EACCES,
    EBADF,
    EFAULT,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOTDIR,
    EOVERFLOW,
#endif /* __linux__ */
};

static const int errno_getxattr[] = {
#ifdef __linux__
    E2BIG,
    ENODATA,
    ENOTSUP,
    ERANGE,
    /* In addition, the errors documented in stat(2) can also occur. */
    EACCES,
    EBADF,
    EFAULT,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOTDIR,
    EOVERFLOW,
#endif /* __linux__ */
};

static const int errno_listxattr[] = {
#ifdef __linux__
    E2BIG,
    ENOTSUP,
    ERANGE,
    /* In addition, the errors documented in stat(2) can also occur. */
    EACCES,
    EBADF,
    EFAULT,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOTDIR,
    EOVERFLOW,
#endif /* __linux__ */
};

static const int errno_removexattr[] = {
#ifdef __linux__
    ENODATA,
    ENOTSUP,
    /* In addition, the errors documented in stat(2) can also occur. */
    EACCES,
    EBADF,
    EFAULT,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOMEM,
    ENOTDIR,
    EOVERFLOW,
#endif /* __linux__ */
};

static int errno_flock[] = {
#ifdef __linux__
    EBADF,
    EINTR,
    EINVAL,
    ENOLCK,
    EWOULDBLOCK,
#endif /* __linux__ */

#ifdef __FreeBSD__
    EBADF,
    EINVAL,
    ENOLCK,
    EOPNOTSUPP,
    EWOULDBLOCK,
#endif /* __FreeBSD__ */
};

static int errno_fallocate[] = {
#ifdef __linux__
    EBADF,
    EFBIG,
    EINTR,
    EINVAL,
    EIO,
    ENODEV,
    ENOSPC,
    ENOSYS,
    EOPNOTSUPP,
    EPERM,
    ESPIPE,
    ETXTBSY,
#endif /* __linux__ */
};

static int errno_ioctl[] = {
#if defined(__linux__) || defined(__FreeBSD__)
    EBADF,
    EFAULT,
    EINVAL,
    ENOTTY,
#endif /* __linux__  || __FreeBSD__ */
};

static const int errno_fcntl[] = {
#ifdef __linux__
    EACCES,
    EAGAIN,
    EBADF,
    EBUSY,
    EDEADLK,
    EFAULT,
    EINTR,
    EINVAL,
    EMFILE,
    ENOLCK,
    ENOTDIR,
    EPERM,
#endif /* __linux__ */

#ifdef __FreeBSD__
    EAGAIN,
    EBADF,
    EDEADLK,
    EINTR,
    EINVAL,
    EMFILE,
    ENOLCK,
    ENOTTY,
    EOPNOTSUPP,
    EOVERFLOW,
    EPERM,
    ESRCH,
#endif /* __FreeBSD__ */

#ifdef __OpenBSD__
    EAGAIN,
    EBADF,
    EDEADLK,
    EINTR,
    EINVAL,
    EMFILE,
    ENOLCK,
    EOVERFLOW,
    ESRCH,
#endif /* __OpenBSD__ */
};

#endif /* ERRINJ_HH */
