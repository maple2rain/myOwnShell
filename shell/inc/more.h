#ifndef _MORE_H
#define _MORE_H

#include <stdio.h>
#include <stdlib.h>
#include "screen.h"
#include "file_cfg.h"
#include "term.h"
#include "debug.h"

#define MAX_WIDTH 128//一行最多显示128个字符

void doMore(FILE *fp);//使用more命令的方式显示文件
int seeMore(FILE *cmd);//读取来自cmd文件的命令并解析

#endif
