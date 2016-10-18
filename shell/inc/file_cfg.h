#ifndef _FILE_CFG_H
#define _FILE_CFG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/io.h>
#include <dirent.h>

#define BUFFER_SIZE 1024

typedef enum filetype{
	no_exist, reg, dir, blk, chr, fifo, lnk, sock
}FileType;

long getFileSize(FILE *fp);//获取文件大小
int getFileLines(FILE *fp);//获取文件行数
FileType getFileType(char *filename);//获取文件类型`
int isRegularFile(char *filename);//判断是否为普通文件
int isDir(char *filename);//判断是否为文件夹

#define EXIST 0
#define W_PERMISSION 2
#define R_PERMISSION 4
#define WR_PERMISSION 6
	
#define isFileExist(filename)\
   (access(filename, EXIST) != -1)

#endif
