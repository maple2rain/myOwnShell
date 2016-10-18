#include "../inc/screen.h"

int getPageLen(void)//获取页面长度
{
	struct winsize info;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &info);
	return info.ws_row;
}

int getPageWidth(void)//获取页面宽度
{
	struct winsize info;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &info);
	return info.ws_col;
}