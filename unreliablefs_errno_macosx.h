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
    EROFS,
    ETXTBSY,
};

static const int errno_chmod[] = {
    EACCES,
    EFAULT,
    EINTR,
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
     EAGAIN,
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
     EOVERFLOW,
     EROFS,
     ETXTBSY,
};

static const int errno_ftruncate[] = {
    EBADF,
    EFBIG,
    EINTR,
    EINVAL,
    EIO,
    EROFS,
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
    EMLINK,
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
    /* TODO */
};

static const int errno_readdir[] = {
    /* TODO */
};

static const int errno_read[] = {
    EAGAIN,
    EBADF,
    ECONNRESET,
    EFAULT,
    EINTR,
    EINVAL,
    EIO,
    EISDIR,
    ENOBUFS,
    ENOMEM,
    ENOTCONN,
    ENXIO,
    ETIMEDOUT,
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
    EINTR,
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
    ECONNRESET,
    EDQUOT,
    EFAULT,
    EFBIG,
    EINTR,
    EINVAL,
    EIO,
    ENETDOWN,
    ENETUNREACH,
    ENOSPC,
    ENXIO,
    EPIPE,
    EWOULDBLOCK,
};

static const int errno_lstat[] = {
    EACCES,
    EFAULT,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
    EOVERFLOW,
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
    ESRCH,
};

static const int errno_fsync[] = {
    EBADF,
    EINTR,
    EINVAL,
    EIO,
};

static const int errno_setxattr[] = {
    E2BIG,
    EACCES,
    EEXIST,
    EFAULT,
    EINVAL,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOATTR,
    ENOSPC,
    ENOTDIR,
    ENOTSUP,
    EPERM,
    ERANGE,
    EROFS,
};

static const int errno_getxattr[] = {
    EACCES,
    EFAULT,
    EINVAL,
    EIO,
    EISDIR,
    ELOOP,
    ENAMETOOLONG,
    ENOATTR,
    ENOTDIR,
    ENOTSUP,
    EPERM,
    ERANGE,
};

static const int errno_listxattr[] = {
    EACCES,
    EFAULT,
    EINVAL,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOTDIR,
    ENOTSUP,
    EPERM,
    ERANGE,
};

static const int errno_removexattr[] = {
    EACCES,
    EFAULT,
    EINVAL,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOATTR,
    ENOTDIR,
    ENOTSUP,
    EPERM,
    EROFS,
};

static int errno_flock[] = {
    EBADF,
    EINVAL,
    ENOTSUP,
    EWOULDBLOCK,
};

static int errno_ioctl[] = {
    EBADF,
    EINVAL,
    ENOTTY,
};

static const int errno_fcntl[] = {
    EACCES,
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
