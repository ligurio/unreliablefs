#ifndef ERRINJ_HH
#define ERRINJ_HH

#include <errno.h>
#include <signal.h>

#include "unreliablefs_ops.h"

#define MAX_ERRINJ_NAME_LENGTH 20
#define MIN_PROBABLITY 0
#define MAX_PROBABLITY 100
#define DEFAULT_SIGNAL_NAME SIGKILL

int error_inject(const char* path, fuse_op operation);
struct err_inj_q *config_init(const char* conf_path);
void config_delete(struct err_inj_q *config);
int conf_option_handler(void* cfg, const char* section,
                        const char* name, const char* value);
int is_regex_matched(const char *regex, const char *string);

const char *errinj_name[] =
{
    "errinj_noop",
    "errinj_kill_caller",
    "errinj_errno",
};

typedef enum {
    ERRINJ_NOOP,
    ERRINJ_KILL_CALLER,
    ERRINJ_ERRNO,
} errinj_type;

typedef struct errinj_conf errinj_conf;

struct errinj_conf {
    char *err_injection_name;
    char *op_regexp;
    char *path_regexp;
    char *errno_regexp;
    int probability;
    errinj_type type;

    TAILQ_ENTRY(errinj_conf) entries;
};

TAILQ_HEAD(err_inj_q, errinj_conf);

static const int errno_access[] = {
    EACCES,
    EINVAL,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
    EROFS,
    ETXTBSY
};

static const int errno_chmod[] = {
    EACCES,
    EINTR,
    EINVAL,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
    EPERM,
    EROFS
};

static const int errno_creat[] = {
    EACCES,
    EAGAIN,
    EEXIST,
    EINTR,
    EINVAL,
    EIO,
    EISDIR,
    ELOOP,
    EMFILE,
    ENAMETOOLONG,
    ENFILE,
    ENOENT,
    ENOMEM,
    ENOSPC,
#if !defined(__FreeBSD__)
    ENOSR,
#endif /* FreeBSD */
    ENOTDIR,
    ENXIO,
    EOPNOTSUPP,
    EOVERFLOW,
    EROFS,
    ETXTBSY
};

static const int errno_ftruncate[] = {
    EBADF,
    EFBIG,
    EINTR,
    EINVAL,
    EIO
};

static const int errno_link[] = {
    EACCES,
    EEXIST,
    ELOOP,
    EMLINK,
    ENAMETOOLONG,
    ENOENT,
    ENOSPC,
    ENOTDIR,
    EPERM,
    EROFS,
    EXDEV
};

static const int errno_mkdir[] = {
    EACCES,
    EEXIST,
    ELOOP,
    EMLINK,
    ENAMETOOLONG,
    ENOENT,
    ENOSPC,
    ENOTDIR,
    EROFS
};

static const int errno_mknod[] = {
    EACCES,
    EEXIST,
    EINVAL,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOSPC,
    ENOTDIR,
    EPERM,
    EROFS
};

static const int errno_opendir[] = {
    EACCES,
    ELOOP,
    EMFILE,
    ENAMETOOLONG,
    ENFILE,
    ENOENT,
    ENOTDIR
};

static const int errno_readdir[] = {
    EBADF,
    ENOENT,
    EOVERFLOW,
};

static const int errno_read[] = {
    EAGAIN,
    EBADF,
    EBADMSG,
    ECONNRESET,
    EINTR,
    EINVAL,
    EIO,
    EISDIR,
    ENOBUFS,
    ENOMEM,
    ENOTCONN,
    ENXIO,
    EOVERFLOW,
    ETIMEDOUT,
    EWOULDBLOCK
};

static const int errno_readlink[] = {
    EACCES,
    EINVAL,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR
};

static const int errno_rename[] = {
    EACCES,
    EBUSY,
    EEXIST,
    EINVAL,
    EIO,
    EISDIR,
    ELOOP,
    EMLINK,
    ENAMETOOLONG,
    ENOENT,
    ENOSPC,
    ENOTDIR,
    ENOTEMPTY,
    EPERM,
    EROFS,
    ETXTBSY,
    EXDEV
};

static const int errno_rmdir[] = {
    EACCES,
    EBUSY,
    EEXIST,
    EINVAL,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
    ENOTEMPTY,
    EPERM,
    EROFS
};

static const int errno_symlink[] = {
    EACCES,
    EEXIST,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOSPC,
    ENOTDIR,
    EROFS
};

static const int errno_truncate[] = {
    EACCES,
    EFBIG,
    EINTR,
    EINVAL,
    EIO,
    EISDIR,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
    EROFS
};

static const int errno_unlink[] = {
    EACCES,
    EBUSY,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
    EPERM,
    EROFS,
    ETXTBSY
};

static const int errno_write[] = {
    EACCES,
    EAGAIN,
    EBADF,
    EFBIG,
    EINTR,
    EINVAL,
    EIO,
    ENETDOWN,
    ENETUNREACH,
    ENOBUFS,
    ENOSPC,
    ENXIO,
    ERANGE
};

static const int errno_lstat[] = {
#if defined(__OpenBSD__) || defined(__FreeBSD__)
    ENOTDIR,
    EIO,
#endif /* __OpenBSD__ || __FreeBSD__ */
    ENAMETOOLONG,
    ENOENT,
    EACCES,
    ELOOP,
    EFAULT,
#if defined(__Linux__)
    ENOMEM,
#endif /* __Linux__ */

#if defined(__Linux__) || defined(__FreeBSD__)
    EBADF,
    EOVERFLOW,
#endif /* __Linux__ || __FreeBSD__ */

#ifdef __FreeBSD__
     EINTEGRITY,
     EINVAL,
#endif /* __FreeBSD__ */
};

static const int errno_statfs[] = {
    /* OpenBSD */
    ENOTDIR,
    ENAMETOOLONG,
    ENOENT,
    EACCES,
    ELOOP,
    EFAULT,
    EIO,

    /* Linux */
    /*
    EACCES
    EFAULT
    EINTR
    EIO
    ELOOP
    ENAMETOOLONG
    ENOENT
    ENOMEM
    ENOSYS
    ENOTDIR
    EOVERFLOW
    */

    /* FreeBSD */
    /*
    ENOTDIR
    ENAMETOOLONG
    ENOENT
    EACCES
    ELOOP
    EFAULT
    EIO
    EINTEGRITY
    */
};

static const int errno_close[] = {
    /* Linux */
    EBADF,
    EINTR,
    EIO,
    ENOSPC,
    EDQUOT,

/* FreeBSD */
    EBADF,
    EINTR,
    ENOSPC,
    ECONNRESET,

/* OpenBSD */
    EBADF,
    EINTR,
    EIO,
};

static const int errno_utimensat[] = {
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
#ifdef __FreeBSD__
    EIO,
    EINTEGRITY,
#endif /* __FreeBSD__ */
};

static const int errno_fsync[] = {
    EBADF,
    EIO,
    EINVAL,
#ifdef __Linux__
    EDQUOT
    ENOSPC
    EROFS
#endif /* __Linux__ */

#ifdef __FreeBSD__
    EINTEGRITY
#endif /* __FreeBSD__ */
};

#ifdef HAVE_XATTR
static const int errno_setxattr[] = {
    /* Linux */
    EDQUOT,
    EEXIST,
    ENODATA,
    ENOSPC,
    ENOTSUP,
    EPERM,
    /* In addition, the errors documented in stat(2) can also occur. */
    ERANGE,
};
#endif /* HAVE_XATTR */

#ifdef HAVE_XATTR
static const int errno_getxattr[] = {
    E2BIG,
    ENODATA,
    ENOTSUP,
    ERANGE,
    /* In addition, the errors documented in stat(2) can also occur. */
};
#endif /* HAVE_XATTR */

#ifdef HAVE_XATTR
static const int errno_listxattr[] = {
    E2BIG,
    ENOTSUP,
    ERANGE,
    /* In addition, the errors documented in stat(2) can also occur. */
};
#endif /* HAVE_XATTR */

#ifdef HAVE_XATTR
static const int errno_removexattr[] = {
    ENODATA,
    ENOTSUP,
    /* In addition, the errors documented in stat(2) can also occur. */
};
#endif /* HAVE_XATTR */

static int errno_flock[] = {
    EBADF,
    EINVAL,
    ENOLCK,
    EWOULDBLOCK,
    /* Linux */
#ifdef __Linux__
    EINTR,
#endif /* __Linux__ */

#ifdef __Linux__
    EOPNOTSUPP,
#endif /* __FreeBSD__ */
};

static int errno_fallocate[] = {
    EBADF,
    EFBIG,
    EINTR,
    EINVAL,
    EIO,
    ENODEV,
    ENOSYS,
    EOPNOTSUPP,
    EPERM,
    ESPIPE,
    ETXTBSY,
};

static int errno_ioctl[] = {
    EBADF,
    EFAULT,
    EINVAL,
    ENOTTY,
};

static const int errno_fcntl[] = {
    /* Linux */
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

    /* FreeBSD */
/*
    EAGAIN
    EBADF
    EDEADLK
    EINTR
    EINVAL
    EMFILE
    ENOTTY
    ENOLCK
    EOPNOTSUPP
    EOVERFLOW
    EPERM
    ESRCH
*/

    /* OpenBSD */
/*
    EAGAIN
    EBADF
    EDEADLK
    EINTR
    EINVAL
    EMFILE
    ENOLCK
    EOVERFLOW
    ESRCH
*/
};

#endif /* ERRINJ_HH */
