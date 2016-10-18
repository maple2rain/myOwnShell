#include "../inc/file_cfg.h" 

//返回文件的字节数，由调用者负责检测文件指针是否有效
long getFileSize(FILE *fp)
{
	long n;
	fseek(fp, 0, SEEK_END);
	n = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	return n;
}

//返回文件的行数
int getFileLines(FILE *fp)
{
	int lines = 0;
	char buf[BUFFER_SIZE];
	size_t bufLength;

	while(bufLength = fread(buf, sizeof(char),  BUFFER_SIZE, fp)){
		for(int i = 0; i < bufLength; ++i)
			if(buf[i] == '\n')
				lines++;
	}
	
	fseek(fp, 0, SEEK_SET);
	return lines;
}

FileType getFileType(char *filename)
{
	struct stat info;
	if(stat(filename, &info) != -1){
		if(S_ISREG(info.st_mode))
			return reg;
		else if(S_ISDIR(info.st_mode))
			return dir;
		else if(S_ISBLK(info.st_mode))
			return blk;
		else if(S_ISCHR(info.st_mode))
			return chr;
		else if(S_ISFIFO(info.st_mode))
			return fifo;
		else if(S_ISLNK(info.st_mode))
			return lnk;
		else if(S_ISSOCK(info.st_mode))
			return sock;
	}
	else{
		perror(filename);
		return no_exist;
	}
}

int isRegularFile(char *filename)
{
	if(reg == getFileType(filename))
		return 1;
	else
		return 0;
}

int isDir(char *filename)
{
	if(dir == getFileType(filename))
		return 1;
	else
		return 0;
}
