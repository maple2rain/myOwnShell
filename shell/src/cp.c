#include "../inc/cp.h"

#define BUFFER_LEN 4096
#define COPY_MODE 0644
#define MKDIR_MODE 0755

void CopyF2F(char *inFilename, char *outFilename)
{
	int inFd, outFd, rLen;
	char buf[BUFFER_LEN];

	if((inFd = open(inFilename, O_RDONLY)) == -1){
		perror(inFilename);
		return ;
	}

	if((outFd = creat(outFilename, COPY_MODE)) == -1){
		perror(outFilename);
		return ;
	}

	while((rLen = read(inFd, buf, BUFFER_LEN)) > 0){
		if(write(outFd, buf, rLen) != rLen)
			oops("write error to", outFilename);
	}

	if(rLen == -1)
		oops("read error from", inFilename);//文件夹无法使用read读取？

}

void CopyPath(char *filename, char *dirname, char *dstName)
{
	strcpy(dstName, dirname);
	strcat(dstName, "/");
	strcat(dstName, filename);
}

void CopyF2D(char *filename, char *dirname)
{
	char dstName[256];
	CopyPath(filename, dirname, dstName);
	CopyF2F(filename, dstName);
}

void CopyDir(char *inDirname, char *outDirname)
{
	char *filename = inDirname;

	while(*inDirname){
		if(*inDirname == '/')
			if(*(inDirname + 1))
				filename = inDirname + 1;//找到目录名，去除多余路径名
			else
				*inDirname = '\0';//最后一个字符为反斜杠，则去除之
		inDirname++;
	}
	
	CopyPath(filename, outDirname, outDirname);
	if(-1 == mkdir(outDirname, MKDIR_MODE))
		oops("mkdir error", outDirname);
}

void CopyD2D(char *inDirname, char *outDirname)
{
	DIR *dir_ptr;
	struct dirent *dirent_ptr;
	char OutDir[256];
	char InDir[256];
	int flag = 0;//指示为.和..文件的flag，创建时需跳过

	strcpy(InDir, inDirname);
	DEBUG_PRINT("Indir is %s\n", InDir);
	strcpy(OutDir, outDirname);
	DEBUG_PRINT("Outdir is %s\n", OutDir);
	CopyDir(InDir, OutDir);

	if((dir_ptr = opendir(InDir)) == NULL)
		oops("opendir error", InDir);
	
	while((dirent_ptr = readdir(dir_ptr)) != NULL){
		char dstName[256];
		if(++flag <= 2)
			continue;
		strcpy(dstName, OutDir);
		if(isRegularFile(dirent_ptr->d_name))
			CopyF2D(dirent_ptr->d_name, dstName);
		else
			CopyD2D(dirent_ptr->d_name, dstName);
	}
	closedir(dir_ptr);
}


int main(int argc, char *argv[])
{
	struct stat infoLast;
	FileType dstFlag = no_exist;
	if(argc < 3)
		oops("usage error", argv[0]);

	if(isFileExist(argv[argc - 1])){
		dstFlag = 1;

		if((stat(argv[argc - 1], &infoLast) == -1))
			oops("meseage read error", argv[argc - 1]);
	
		if(dstFlag && S_ISDIR(infoLast.st_mode))
			dstFlag = 2;
	}

	if(argc > 3){
		if(dstFlag && dstFlag != 2)//参数多余3个时，最后一个不是目录则出错
			oops("usage error", argv[argc - 1]);
	}

	while(--argc > 1){
		struct stat infoPrv;
		if(stat(*++argv, &infoPrv) == -1){
			perror(*argv);
			continue;
		}
		
		if(S_ISREG(infoPrv.st_mode)){
			if(dstFlag == 1)//复制文件到文件
				CopyF2F(*argv, argv[argc - 1]);
			else//复制文件到文件夹中
				CopyF2D(*argv, argv[argc - 1]);
		}
		else{
			if(dstFlag == 1)//欲将文件夹覆盖至文件
				oops("override file with dir", argv[argc -1]);
			CopyD2D(*argv, argv[argc - 1]);
		}
	}
	return 0;
}
