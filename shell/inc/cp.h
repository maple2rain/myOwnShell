#ifndef _CP_H
#define _CP_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include "debug.h"
#include "file_cfg.h"

void CopyF2F(char *inFilename, char *outFilename);
void CopyF2D(char *filename, char *dirname);
void CopyD2D(char *inDirname, char *outDirname);

#endif
