/* this is a stub for dirent.c functions used in HA archiver code */
/* Copyright (c) 2024, by val khokhlov */
#include <stdio.h>
#include "dirent.h"
#include "machine.h"

DIR *opendir(const char *path) {
  DIR *dir;
  int len;

  dir = malloc(sizeof(DIR));
  len = strlen(path);
  dir->path = malloc(len + 1 + strlen(ALLFILES) + 1);
  strcpy(dir->path, path);
  if (path[len-1] != '\\' && path[len-1] != '/' && path[len-1] != ':') 
    dir->path[len++] = '\\';
  strcpy(dir->path + len, ALLFILES);
  dir->hFind = FindFirstFile(dir->path, &(dir->FindFileData));
  if (dir->hFind == INVALID_HANDLE_VALUE) {
    free(dir->path);
    free(dir);
    return NULL;
  }
  dir->current_pos = 0;
  return dir;
}

struct dirent *readdir(DIR *dir) {
  if (dir->current_pos == -1) return NULL;
  strncpy(dir->ent.d_name, dir->FindFileData.cFileName, PATH_MAX);
  dir->ent.d_name[PATH_MAX] = 0;
  dir->ent.d_namlen = strlen(dir->ent.d_name);
  //ent->d_type = datap->dwFileAttributes;
  if (FindNextFile(dir->hFind, &(dir->FindFileData))) dir->current_pos++;
    else dir->current_pos = -1;
  return &(dir->ent);
}

int closedir(DIR *dir) {
  if (dir) {
    if (dir->path) free(dir->path);
    free(dir);
    return 0;
  }
  return -1;
}
