#ifndef ERRNO_HH
#define ERRNO_HH

#include <sys/param.h>
#include <errno.h>

static const int errno_access[] = {
    EACCES,
    EFAULT,
#if __FreeBSD__ >= 12
    EINTEGRITY,
#endif
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
    EFTYPE,
#if __FreeBSD__ >= 12
    EINTEGRITY,
#endif
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
    EPERM,
    EPERM,
    EROFS,
};

static const int errno_creat[] = {
    EACCES,
    EBADF,
    ECAPMODE,
    EDQUOT,
    EEXIST,
    EFAULT,
#if __FreeBSD__ >= 12
    EINTEGRITY,
#endif
    EINTR,
    EINVAL,
    EIO,
    EISDIR,
    ELOOP,
    EMFILE,
    EMLINK,
    ENAMETOOLONG,
    ENFILE,
    ENOENT,
    ENOSPC,
    ENOTCAPABLE,
    ENOTDIR,
    ENXIO,
    EOPNOTSUPP,
    EPERM,
    EROFS,
    ETXTBSY,
    EWOULDBLOCK,
};

static const int errno_ftruncate[] = {
    EACCES,
    EBADF,
    EFAULT,
    EFBIG,
#if __FreeBSD__ >= 12
    EINTEGRITY,
#endif
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
};

static const int errno_link[] = {
    EACCES,
    EBADF,
    EDQUOT,
    EEXIST,
    EFAULT,
#if __FreeBSD__ >= 12
    EINTEGRITY,
#endif
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
};

static const int errno_mkdir[] = {
    EACCES,
    EBADF,
    EDQUOT,
    EEXIST,
    EFAULT,
#if __FreeBSD__ >= 12
    EINTEGRITY,
#endif
    EIO,
    ELOOP,
    EMLINK,
    ENAMETOOLONG,
    ENOENT,
    ENOSPC,
    ENOTDIR,
    EPERM,
    EROFS,
};

static const int errno_mknod[] = {
    EACCES,
    EBADF,
    EDQUOT,
    EEXIST,
    EFAULT,
#if __FreeBSD__ >= 12
    EINTEGRITY,
#endif
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
    EACCES,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
};

static const int errno_readdir[] = {
    EBADF,
    EFAULT,
#if __FreeBSD__ >= 12
    EINTEGRITY,
#endif
    EINVAL,
    EIO,
};

static const int errno_read[] = {
    EAGAIN,
    EBADF,
    EBUSY,
    ECONNRESET,
    EFAULT,
#if __FreeBSD__ >= 12
    EINTEGRITY,
#endif
    EINTR,
    EINVAL,
    EIO,
    EISDIR,
    EOPNOTSUPP,
    EOVERFLOW,
};

static const int errno_readlink[] = {
    EACCES,
    EFAULT,
#if __FreeBSD__ >= 12
    EINTEGRITY,
#endif
    EINVAL,
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
};

static const int errno_rename[] = {
    EACCES,
    ECAPMODE,
    EDQUOT,
    EFAULT,
#if __FreeBSD__ >= 12
    EINTEGRITY,
#endif
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
#if __FreeBSD__ >= 12
    EINTEGRITY,
#endif
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
#if __FreeBSD__ >= 12
    EINTEGRITY,
#endif
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOSPC,
    ENOTDIR,
    EPERM,
    EROFS,
};

static const int errno_truncate[] = {
    EACCES,
    EFAULT,
    EFBIG,
#if __FreeBSD__ >= 12
    EINTEGRITY,
#endif
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
};

static const int errno_unlink[] = {
    EACCES,
    EFAULT,
#if __FreeBSD__ >= 12
    EINTEGRITY,
#endif
    EIO,
    EISDIR,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOSPC,
    ENOTDIR,
    EPERM,
    EROFS,
};

static const int errno_write[] = {
    EAGAIN,
    EBADF,
    EDQUOT,
    EFAULT,
    EFBIG,
#if __FreeBSD__ >= 12
    EINTEGRITY,
#endif
    EINTR,
    EINVAL,
    EIO,
    ENOSPC,
    EPIPE,
    EROFS,
};

static const int errno_lstat[] = {
    EACCES,
    EFAULT,
#if __FreeBSD__ >= 12
    EINTEGRITY,
#endif
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
#if __FreeBSD__ >= 12
    EINTEGRITY,
#endif
    EIO,
    ELOOP,
    ENAMETOOLONG,
    ENOENT,
    ENOTDIR,
};

static const int errno_close[] = {
    EBADF,
    EINTR,
    ENOSPC,
    ECONNRESET,
};

static const int errno_utimensat[] = {
    EACCES,
    EBADF,
    EFAULT,
#if __FreeBSD__ >= 12
    EINTEGRITY,
#endif
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
#if __FreeBSD__ >= 12
    EINTEGRITY,
#endif
    EINVAL,
    EIO,
};

static int errno_flock[] = {
    EBADF,
    EINVAL,
    ENOLCK,
    EOPNOTSUPP,
    EWOULDBLOCK,
};

static int errno_ioctl[] = {
    EBADF,
    EFAULT,
    EINVAL,
    ENOTTY,
};

static const int errno_fcntl[] = {
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
};

#endif /* ERRNO_HH */
