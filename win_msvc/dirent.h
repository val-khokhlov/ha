/* this is a stub for dirent.h functions used in HA archiver code */
/* Copyright (c) 2024, by val khokhlov */

#ifndef DIRENT_H
#define DIRENT_H

#include <windows.h>

#if !defined(PATH_MAX)
#define PATH_MAX _MAX_PATH
#endif

struct dirent {
  long d_ino;
  long d_off;
  unsigned short d_reclen;
  size_t d_namlen;
  int d_type;
  char d_name[PATH_MAX+1];
};
typedef struct dirent dirent;

struct DIR {
  struct dirent ent;
  char *path;
  int current_pos;
  HANDLE hFind;
  WIN32_FIND_DATA FindFileData;
};
typedef struct DIR DIR;

DIR *opendir(const char *path);
struct dirent *readdir(DIR *dir);
int closedir(DIR *dir);

#endif /* DIRENT_H */
