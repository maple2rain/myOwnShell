/*more.c - a command like 'more'
 *read a file and read command from tty
*/
#include "../inc/more.h"

typedef enum effect{
	Quit, NextPage, NextLine
}Effect;

int PAGELEN;
int PAGEWIDTH;

void showUsageMore(void)
{
	printf("Usage:\n");
	printf("more [option] <file>..\n");
}

int main(int argc, char *argv[])
{
	FILE *fp;
	if(argc == 1)
		showUsageMore();
	else{
		while(--argc){//依次读取参数中的文件
			if((fp = fopen(*++argv, "r")) != NULL){
				doMore(fp);
				fclose(fp);
			}
			else
				exit(1);
		}
	}
	return 0;
}

void doMore(FILE *fp)
{
	char line[MAX_WIDTH];
	int numOfLines = 0;
	int reply;
	long precent;
	int curRow, totalRows;
	FILE *fp_tty;

	fp_tty = fopen("/dev/tty", "r");
	if(!fp_tty)
		exit(1);
	CLEAR();
	/*获取页面长度和宽度*/
	PAGELEN = getPageLen() - 1;	
	PAGEWIDTH = getPageWidth() - 1;

	totalRows = getFileLines(fp);//获取文件总行数
	curRow = PAGELEN;//计算当前读取的行数

	DEBUG_PRINT("totalRows is %d, curRow is %d\n", totalRows, curRow);
	while(fgets(line, PAGEWIDTH, fp)){
		if(numOfLines == PAGELEN){
			PAGELEN = getPageLen() - 1;//重新获取页面长度，以免终端大小改变
			REVERSE();//反白
			printf("--more--\(%d%%\)",(int)(((float)curRow / totalRows) * 100));
			CLOSE_EFFECT();//关闭反白
			reply = seeMore(fp_tty);//获取命令

			if(reply == -1){
				GO_NEXT_LINE();
				break;
			}
			curRow += reply;//计算当前读取的行数
			CLEAN_CUR_LINE();	
			numOfLines -= reply;//减去reply行，则可以显示多reply行
		}
		if(fputs(line, stdout) == EOF)
			exit(1);
		numOfLines++;
	}
}

int seeMore(FILE *cmd)
{
	int c;
	while(( c = getch()) != EOF){
		if(c == 'q')
			return -1;
		if(c == ' ')
			return PAGELEN;
		if(c == '\n')
			return 1;
	}
	return 0;
}
