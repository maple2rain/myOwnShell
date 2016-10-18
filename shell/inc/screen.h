#ifndef _SCREEN_H
#define _SCREEN_H

#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <signal.h>

/*define color*/
#define NONE		 	"/033[m"
#define RED 			"/033[0;32;31m"
#define LIGHT_RED	 	"/033[1;31m"
#define GREEN		 	"/033[0;32;32m"
#define LIGHT_GREEN 	"/033[1;32m"
#define BLUE 			"/033[0;32;34m"
#define LIGHT_BLUE		"/033[1;34m"
#define DARY_GRAY 		"/033[1;30m"
#define CYAN 			"/033[0;36m"
#define LIGHT_CYAN		"/033[1;36m"
#define PURPLE 			"/033[0;35m"
#define LIGHT_PURPLE 	"/033[1;35m"
#define BROWN 			"/033[0;33m"
#define YELLOW 			"/033[1;33m"
#define LIGHT_GRAY		"/033[0;37m"
#define WHITE 			"/033[1;37m"

// 清除屏幕
#define CLEAR() printf("\033[2J")

// 上移光标
#define MOVEUP(x) printf("\033[%dA", (x))

// 下移光标
#define MOVEDOWN(x) printf("\033[%dB", (x))

// 左移光标
#define MOVELEFT(y) printf("\033[%dD", (y))

// 右移光标
#define MOVERIGHT(y) printf("\033[%dC",(y))

// 定位光标
#define MOVETO(x,y) printf("\033[%d;%dH", (x), (y))

//返回行首
#define MOVE_TO_HEAD() printf("\r");

// 光标复位
#define RESET_CURSOR() printf("\033[H")

// 隐藏光标
#define HIDE_CURSOR() printf("\033[?25l")

// 显示光标
#define SHOW_CURSOR() printf("\033[?25h")

//取消反显
#define UN_HIGHT_LIGHT() printf("\033[27m")

//关闭所有属性
#define CLOSE_EFFECT() printf("\033[0m")

//设置高亮度
#define HIGH_LIGHT() printf("\033[1m")

//下划线
#define UNDERLINE() printf("\033[4m") 

//闪烁
#define TWINKLE() printf("\033[5m") 

//反显
#define REVERSE() printf("\033[7m") 

//消隐
#define BLANK_OFF() printf("\033[8m") 

//设置字体颜色
#define SET_COLOR(color) printf(color)

//清除从光标到行尾的内容
#define CLEAN2TAIL() printf("\033[K")

//清除当前行
#define CLEAN_CUR_LINE() printf("\r\033[K")

//光标转移到下一行
#define GO_NEXT_LINE() printf("\n")

//获取页面长度
int getPageLen(void);

//获取页面宽度
int getPageWidth(void);

#endif
