#include "../inc/show_time.h"

void showTime(long timeVal)//只显示月日和时分秒
{
	struct tm *t;
	t = localtime(&timeVal);
	printf("%4d-%02d-%02d %2d:%2d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min);//输出年月日时分
}
