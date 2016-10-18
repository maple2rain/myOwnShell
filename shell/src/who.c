#include "../inc/who.h"

#define SHOW_HOST 1

void showInfoWho(struct utmp *rec)
{
	printf("%-8.8s ", rec->ut_user);
	printf("%-8.8s ", rec->ut_line);
	showTime(rec->ut_time);
#if SHOW_HOST
	printf(" \(%s\)", rec->ut_host);
#endif
	printf("\n");
}

utmp_userPtr utmp_open(char *filename)
{
	utmp_userPtr utmpPtr = (utmp_userPtr)malloc(sizeof(utmp_user));
	if(utmpPtr == NULL)
		oops("Malloc failed", "utmp malloc");
	if((utmpPtr->fd_utmp = open(filename, O_RDONLY)) == -1)
	oops("Can't open", filename);
	utmpPtr->recNum = utmpPtr->curNum = 0;
	return utmpPtr;
}

struct utmp *utmp_next(utmp_userPtr utmpPtr)
{
	struct utmp * recPtr;
	if(utmpPtr->curNum == utmpPtr->recNum && utmp_reload(utmpPtr) == 0) 
		return NULL_UTMP;

	recPtr = (struct utmp *)&(utmpPtr->utmpBuf[utmpPtr->curNum * UTSIZE]);
	utmpPtr->curNum++;
	return recPtr;
}

int utmp_reload(utmp_userPtr utmpPtr)
{
	int readNum;
	readNum = read(utmpPtr->fd_utmp, utmpPtr->utmpBuf, UTSIZE * REC_NUM);
	utmpPtr->recNum = readNum / UTSIZE;
	utmpPtr->curNum = 0;
	return utmpPtr->recNum;
}

void utmp_close(utmp_userPtr utmpPtr)
{
	if(utmpPtr->fd_utmp != -1)
		close(utmpPtr->fd_utmp);
	free(utmpPtr);
}


int main(void)
{
	struct utmp	*curRecord = NULL;	//暂存当前读取的记录
	utmp_userPtr utmpPtr = utmp_open(UTMP_FILE);
	
	while((curRecord = utmp_next(utmpPtr)) != NULL_UTMP){
		if(curRecord->ut_type == USER_PROCESS)
			showInfoWho(curRecord);
	}
	utmp_close(utmpPtr);
	exit(0);
}
