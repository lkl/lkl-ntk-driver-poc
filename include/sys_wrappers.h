#ifndef _LKL_SYS_WRAP_H
#define _LKL_SYS_WRAP_H

#include <ddk/ntddk.h>
#undef FASTCALL
#include <asm/lkl.h>
#include <asm/unistd.h>
#include <asm/statfs.h>
#include <asm/stat.h>
#include <asm/types.h>
#undef FASTCALL

typedef struct __kernel_stat    STATS;
typedef struct __kernel_stat*   PSTATS;
typedef struct __kernel_statfs  STATFS;
typedef struct __kernel_statfs* PSTATFS;
typedef struct __kernel_dirent  DIRENT;
typedef struct __kernel_dirent* PDIRENT;


// used to store all the info that we'll need for unmount
typedef struct lin_dev {
      CHAR mnt[255];
      CHAR devno_str[255];
      USHORT mnt_length;
      USHORT devno_str_length;
      __kernel_dev_t devno;
} LINDEV, *PLINDEV;

NTSTATUS InitializeSysWrappers();
void FreeSysWrapperResources();

LONG sys_open_wrapper(IN PCSTR pathName, INT flags, INT mode);
LONG sys_close_wrapper(UINT fd);
LONG sys_read_wrapper(UINT fd, IN PVOID buf, ULONG size);
LONG sys_lseek_wrapper(UINT fd, __kernel_off_t offset, UINT origin);
LONG sys_newfstat_wrapper(UINT fd,OUT PSTATS);
LONG sys_newstat_wrapper(IN PSTR filename,OUT PSTATS statbuf);
LONG sys_statfs_wrapper(IN PCSTR path,OUT PSTATFS);
LONG sys_getdents_wrapper(UINT fd, OUT PDIRENT, UINT count);
LONG sys_mount_wrapper(void *wdev, int sectors, PLINDEV lin_dev);
LONG sys_unmount_wrapper(PLINDEV ldev);
void sys_sync_wrapper();

#endif
