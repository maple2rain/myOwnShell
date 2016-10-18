#include "../inc/cat.h"

#define BUFFER_LEN (4 * KB)

int cat(int argc, char *argv[])
{
	FILE *fp;
	if(argc == 1)
		doCat(stdin);
	else{
		while(--argc){
			if((fp = fopen(*++argv, "r")) != NULL){
				doCat(fp);
				fclose(fp);
			}
			else
				oops("Can't open!", *argv);
		}
	}
	return 0;
}

void doCat(FILE *fp)
{
	char buf[BUFFER_LEN];
	
	while(fread(buf, sizeof(char), BUFFER_LEN, fp)){
		if(fputs(buf, stdout) == EOF)
			exit(1);
	}
}
