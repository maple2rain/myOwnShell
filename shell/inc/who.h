#ifndef _WHO_H
#define _WHO_H

#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include "show_time.h"


#define REC_NUM 16
#define NULL_UTMP ((struct utmp *)NULL)
#define UTSIZE (sizeof(struct utmp))

typedef struct utmp_user{
	char utmpBuf[REC_NUM * UTSIZE];//记录若干个utmp数据
	int recNum;//当前从文件中读取到的记录个数
	int curNum;//当前正在处理的记录下标
	int fd_utmp;//文件描述符
}utmp_user, *utmp_userPtr;

utmp_userPtr utmp_open(char *filename);
struct utmp *utmp_next(utmp_userPtr utmpPtr);
int utmp_reload(utmp_userPtr utmpPtr);
void utmp_close(utmp_userPtr utmpPtr);
void showInfoWho(struct utmp *rec);

#endif
