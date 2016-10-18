#include "../inc/cat.h"

#define BUFFER_LEN (4 * KB)

typedef struct record{
	int lines;
	int numOfFiles;
	char *option;
}Record, *RecordPtr;

Status isIntegerStr(char *str)//判断是否为数字字符串
{
	while(*str){
		if(*str > '9' || *str < '0')
			return FALSE;
		str++;
	}
	return TRUE;
}

RecordPtr manageArray(char *str[], int num)
{
	int head, tail;
	RecordPtr record = (RecordPtr)malloc(sizeof(Record));
	if(!record)
		oops("Malloc, failed", "head");

	record->lines = 10;
	head = tail = 0;
	while(num--){
		if(0 == strcmp("-n", str[tail]) || 0 == strcmp("-c", str[tail])){
			if(num == 0){//"-n"后没有参数
				oops("Need a argument!", "head");
			}
			++tail;
			if(FALSE == isIntegerStr(str[tail])){//"-n"后参数不是数字
				oops("Argument must be an integer!", "head");
			}else{
				/*记录选项参数*/	
				record->lines = atoi(str[tail]);
				record->option = str[tail - 1];
			}
			++tail;
			--num;
		}
		else{
			str[head++] = str[tail++];//向前移动字符串
		}
	}
	record->numOfFiles = head;
	return record;
}

void headOp_n(FILE *fp, int len)
{
	char buf[BUFFER_LEN + 1];//多余一位以放置字符0，省去判断
	int rLen, lines = 0;

	while(len > 0){
		rLen = fread(buf, sizeof(char), BUFFER_LEN, fp);
		for(int i = 0; i < rLen; ++i){
			if(buf[i] == '\n'){//计算换行的数量
				lines++;
				if(lines == len){
					buf[i + 1] = '\0';//换行数目已达目标
					break;
				}
			}
		}
		len -= lines;
		if(fputs(buf, stdout) == EOF)
			exit(1);
	}	
}

void headOp_c(FILE *fp, int len)
{
	char buf[BUFFER_LEN + 1];
	int rLen, rest = 0;

	while(len > 0){
		rLen = fread(buf, sizeof(char), BUFFER_LEN, fp);
		if(len <= rLen)//若欲读取长度小于当前文件读取长度，则可省略多余部分
			buf[len] = '\0';

		len -= rLen;//减去已经读取的长度
		if(fputs(buf, stdout) == EOF)
			exit(1);
		printf("len is %d\n", len);
	}
}

void doHead(FILE *fp, char *option, int len)
{
	if(0 == strcmp("-n", option))
		headOp_n(fp, len);
	else if(0 == strcmp("-c", option))
		headOp_c(fp,len);
}

int main(int argc, char *argv[])
{
	FILE *fp;
	RecordPtr record;
	if(argc == 1)
		doCat(stdin);
	else
	{
		record = manageArray(argv + 1, argc - 1);
		while(record->numOfFiles--){
			if((fp = fopen(*++argv, "r")) != NULL){
				printf("<==== %s ====>\n", *argv);
				doHead(fp, record->option, record->lines);
				fclose(fp);
			}
			else{
				perror(*argv);
			}
		}
	}
	return 0;
}

