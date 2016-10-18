/*more.c - a command like 'more'
 *read a file and read command from tty
*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define PAGELEN 23
#define LINELEN 512

typedef enum effect{
	Quit, NextPage, NextLine
}Effect;

void do_more(FILE *fp);
int see_more(FILE *cmd);

int main(int argc, char *argv[])
{
	FILE *fp;
	if(argc == 1)
		do_more(stdin);
	else{
		while(--argc){
			if((fp = fopen(*++argv, "r")) != NULL){
				do_more(fp);
				fclose(fp);
			}
			else
				exit(1);
		}
	}
	return 0;
}

void do_more(FILE *fp)
{
	char line[LINELEN];
	int numOfLines = 0;
	int reply;
	FILE *fp_tty;

	fp_tty = fopen("/dev/tty", "r");
	if(!fp_tty)
		exit(1);
		
	while(fgets(line, LINELEN, fp)){
		if(numOfLines == PAGELEN){
			reply = see_more(fp_tty);
			if(reply == -1)
				break;
			numOfLines -= reply;
		}
		if(fputs(line, stdout) == EOF)
			exit(1);
		numOfLines++;
	}
}

int see_more(FILE *cmd)
{
	int c;
	printf("\033[7m more? \033[m");
	while(( c = getch(cmd)) != EOF){
		if(c == 'q')
			return -1;
		if(c == ' ')
			return PAGELEN;
		if(c == '\n')
			return 1;
	}
	return 0;
}
