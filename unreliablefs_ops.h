#ifndef UNRELIABLEFS_OPS_HH
#define UNRELIABLEFS_OPS_HH

#define FUSE_USE_VERSION 29

#include <fuse.h>

int unreliable_getattr(const char *, struct stat *);
int unreliable_readlink(const char *, char *, size_t);
int unreliable_mknod(const char *, mode_t, dev_t);
int unreliable_mkdir(const char *, mode_t);
int unreliable_unlink(const char *);
int unreliable_rmdir(const char *);
int unreliable_symlink(const char *, const char *);
int unreliable_rename(const char *, const char *);
int unreliable_link(const char *, const char *);
int unreliable_chmod(const char *, mode_t);
int unreliable_chown(const char *, uid_t, gid_t);
int unreliable_truncate(const char *, off_t);
int unreliable_open(const char *, struct fuse_file_info *);
int unreliable_read(const char *, char *, size_t, off_t,
                    struct fuse_file_info *);
int unreliable_write(const char *, const char *, size_t, off_t,
                     struct fuse_file_info *);
int unreliable_statfs(const char *, struct statvfs *);
int unreliable_flush(const char *, struct fuse_file_info *);
int unreliable_release(const char *, struct fuse_file_info *);
int unreliable_fsync(const char *, int, struct fuse_file_info *);
#if !defined(__OpenBSD__) && !defined(__FreeBSD__)
int unreliable_setxattr(const char *, const char *, const char *, size_t, int);
int unreliable_getxattr(const char *, const char *, char *, size_t);
int unreliable_listxattr(const char *, char *, size_t);
int unreliable_removexattr(const char *, const char *);
#endif /* __OpenBSD__ */
int unreliable_opendir(const char *, struct fuse_file_info *);
int unreliable_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                    off_t offset, struct fuse_file_info *fi);
int unreliable_releasedir(const char *, struct fuse_file_info *);
int unreliable_fsyncdir(const char *, int, struct fuse_file_info *);

void *unreliable_init(struct fuse_conn_info *conn);
void unreliable_destroy(void *private_data);

int unreliable_lstat(const char *path, struct stat *statbuf);
int unreliable_access(const char *, int);
int unreliable_create(const char *, mode_t, struct fuse_file_info *);
int unreliable_ftruncate(const char *, off_t, struct fuse_file_info *);
int unreliable_fgetattr(const char *, struct stat *, struct fuse_file_info *);
int unreliable_lock(const char *, struct fuse_file_info *, int cmd,
                 struct flock *);
#if !defined(__OpenBSD__) && !defined(__FreeBSD__) && !defined(__APPLE__)
int unreliable_ioctl(const char *, int cmd, void *arg,
                  struct fuse_file_info *, unsigned int flags, void *data);
#endif /* __OpenBSD__ */
int unreliable_write_buf(const char *, struct fuse_bufvec *buf, off_t off,
                      struct fuse_file_info *);
int unreliable_read_buf(const char *, struct fuse_bufvec **bufp,
                     size_t size, off_t off, struct fuse_file_info *);
#if !defined(__OpenBSD__) && !defined(__FreeBSD__) && !defined(__APPLE__)
int unreliable_flock(const char *, struct fuse_file_info *, int op);
int unreliable_fallocate(const char *, int, off_t, off_t,
                      struct fuse_file_info *);
#endif /* __OpenBSD__ */

#ifdef HAVE_UTIMENSAT
int unreliable_utimens(const char *path, const struct timespec ts[2]);
#endif

#endif /* UNRELIABLEFS_OPS_HH */
