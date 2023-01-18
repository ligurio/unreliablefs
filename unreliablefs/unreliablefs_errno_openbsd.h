#ifndef ERRNO_HH
#define ERRNO_HH

#include <errno.h>

static const int errno_access[] = {
    EACCES,
    EFAULT,
    EINVAL,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
    EPERM,
    EROFS,
    ETXTBSY,
};

static const int errno_chmod[] = {
    EACCES,
    EFAULT,
    EINVAL,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
    EPERM,
    EROFS,
};

static const int errno_creat[] = {
    EACCES,
    EBUSY,
    EDQUOT,
    EEXIST,
    EFAULT,
    EINTR,
    EINVAL,
    EIO,
    EISDIR,
    ELOOP,
    EMFILE,
    ENAMETOOLONG,
    ENFILE,
    ENOENT,
    ENOSPC,
    ENOTDIR,
    ENXIO,
    EOPNOTSUPP,
    EPERM,
    EROFS,
    ETXTBSY,
    EWOULDBLOCK,
};

static const int errno_ftruncate[] = {
    EBADF,
    EFBIG,
    EINVAL,
    EIO,
};

static const int errno_link[] = {
    EACCES,
    EDQUOT,
    EEXIST,
    EFAULT,
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
};

static const int errno_mkdir[] = {
    EACCES,
    EDQUOT,
    EEXIST,
    EFAULT,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOSPC,
    ENOTDIR,
    EROFS,
};

static const int errno_mknod[] = {
    EACCES,
    EDQUOT,
    EEXIST,
    EFAULT,
    EINVAL,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOSPC,
    ENOTDIR,
    EPERM,
    EROFS,
};

static const int errno_opendir[] = {
    /* opendir(2) */
    ENOTDIR,
    /* fcntl(2) */
    EAGAIN,
    EBADF,
    EDEADLK,
    EINTR,
    EINVAL,
    EMFILE,
    ENOLCK,
    EOVERFLOW,
    ESRCH,
    /* fcstat(2) */
    EBADF,
    EFAULT,
    EIO,
    /* open(2) */
    EACCES,
    EBUSY,
    EDQUOT,
    EEXIST,
    EFAULT,
    EINTR,
    EINVAL,
    EIO,
    EISDIR,
    ELOOP,
    EMFILE,
    ENAMETOOLONG,
    ENFILE,
    ENOENT,
    ENOSPC,
    ENOTDIR,
    ENXIO,
    EOPNOTSUPP,
    EPERM,
    EROFS,
    ETXTBSY,
    EWOULDBLOCK,
    /* malloc(2) */
    ENOMEM,
};

static const int errno_readdir[] = {
    EBADF,
    EFAULT,
    EINVAL,
    EIO,
};

static const int errno_read[] = {
    EAGAIN,
    EBADF,
    EFAULT,
    EINTR,
    EINVAL,
    EIO,
    EISDIR,
    ENOTCONN,
};

static const int errno_readlink[] = {
    EACCES,
    EFAULT,
    EINVAL,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
};

static const int errno_rename[] = {
    EACCES,
    EDQUOT,
    EFAULT,
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
    EXDEV,
};

static const int errno_rmdir[] = {
    EACCES,
    EBUSY,
    EFAULT,
    EINVAL,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
    ENOTEMPTY,
    EPERM,
    EROFS,
};

static const int errno_symlink[] = {
    EACCES,
    EDQUOT,
    EEXIST,
    EFAULT,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOSPC,
    ENOTDIR,
    EROFS,
};

static const int errno_truncate[] = {
    EACCES,
    EFAULT,
    EFBIG,
    EINVAL,
    EIO,
    EISDIR,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
    EROFS,
    ETXTBSY,
};

static const int errno_unlink[] = {
    EACCES,
    EBUSY,
    EFAULT,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
    EPERM,
    EROFS,
};

static const int errno_write[] = {
    EAGAIN,
    EBADF,
    EDESTADDRREQ,
    EDQUOT,
    EFAULT,
    EFBIG,
    EINTR,
    EINVAL,
    EIO,
    ENETDOWN,
    ENOSPC,
    EPIPE,
};

static const int errno_lstat[] = {
    EACCES,
    EFAULT,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
};

static const int errno_statfs[] = {
    EACCES,
    EFAULT,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
};

static const int errno_close[] = {
    EBADF,
    EINTR,
    EIO,
};

static const int errno_utimensat[] = {
    EACCES,
    EBADF,
    EFAULT,
    EINVAL,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
    EPERM,
    EROFS,
};

static const int errno_fsync[] = {
    EBADF,
    EINVAL,
    EIO,
};

static int errno_flock[] = {
    EBADF,
    EINVAL,
    EOPNOTSUPP,
    EWOULDBLOCK,
};

static const int errno_fcntl[] = {
    EAGAIN,
    EBADF,
    EDEADLK,
    EINTR,
    EINVAL,
    EMFILE,
    ENOLCK,
    EOVERFLOW,
    ESRCH,
};

#endif /* ERRNO_HH */
