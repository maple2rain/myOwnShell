#include "../inc/cp.h"

#define BUFFER_LEN 4096
#define COPY_MODE 0644
#define MKDIR_MODE 0755

void CopyF2F(char *inFilename, char *outFilename)
{
	int inFd, outFd, rLen;
	char buf[BUFFER_LEN];

	if((inFd = open(inFilename, O_RDONLY)) == -1){//打开待拷贝文件
		DEBUG_PRINT("filename is %s==========\n", inFilename);
		perror(inFilename);
		return ;
	}

	if((outFd = creat(outFilename, COPY_MODE)) == -1){//创建新的文件
		perror(outFilename);
		return ;
	}

	while((rLen = read(inFd, buf, BUFFER_LEN)) > 0){//拷贝数据
		if(write(outFd, buf, rLen) != rLen)
			oops("write error to", outFilename);
	}

	if(rLen == -1)
		oops("read error from", inFilename);//文件夹无法使用read读取？

}

//用于将filename附着在dirname添加/之后，用dstName保存
void CopyPath(char *filename, char *dirname, char *dstName)
{
	strcpy(dstName, dirname);
	strcat(dstName, "/");
	strcat(dstName, filename);
}

//拷贝文件至文件夹下
void CopyF2D(char *filename, char *dirname)
{
	char dstName[256];
	CopyPath(filename, dirname, dstName);
	CopyF2F(filename, dstName);
}

//在outDirname中新建一个inDirname文件夹
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

//将inDirname文件夹拷贝至outDirname文件夹下
void CopyD2D(char *inDirname, char *outDirname)
{
	DIR *dir_ptr;//文件夹指针
	struct dirent *dirent_ptr;//目录项成员指针
	char OutDir[256];//拷贝输出路径，以免修改实参
	int flag = 0;//指示为.和..文件的flag，创建时需跳过

	strcpy(OutDir, outDirname);
	CopyDir(inDirname, OutDir);

	if((dir_ptr = opendir(inDirname)) == NULL)
		oops("opendir error", inDirname);
	
	while((dirent_ptr = readdir(dir_ptr)) != NULL){
		char dstNameIn[256];
		if(++flag <= 2)
			continue;

		if(isDir(dirent_ptr->d_name)){
			char dstNameOut[256];
			strcpy(dstNameOut, OutDir);
			CopyPath(dirent_ptr->d_name, inDirname, dstNameIn);//复制当前文件路径
			CopyD2D(dstNameIn, dstNameOut);//递归拷贝目录
		}
		else
			CopyF2D(dirent_ptr->d_name, OutDir);//拷贝文件至文件夹
	}
	closedir(dir_ptr);
}


int main(int argc, char *argv[])
{
	FileType dstFlag = no_exist;
	if(argc < 3)
		oops("usage error", argv[0]);

	/*判断目标文件是否存在且是否为目录*/
	if(isFileExist(argv[argc - 1])){
		dstFlag = reg;

		if(isDir(argv[argc - 1]))
			dstFlag = dir;
	}

	if(argc > 3){
		if(dstFlag != dir)//参数多余3个时，最后一个不是目录则出错
			oops("usage error", argv[argc - 1]);
	}

	while(--argc > 1){
		if(isDir(*++argv)){
			if(dstFlag == reg)//欲将文件夹覆盖至文件
				oops("override file with dir", argv[argc -1]);
			else if(dstFlag == no_exist){//目标目录不存在
				if(-1 == mkdir(argv[argc -1], MKDIR_MODE))
					oops("mkdir error", argv[argc -1]);
				dstFlag = dir;
			}
			CopyD2D(*argv, argv[argc - 1]);//复制文件夹至文件夹
		}else{
			if(dstFlag == no_exist)//复制文件到文件
				CopyF2F(*argv, argv[argc - 1]);
			else if(dstFlag == dir)//复制文件到文件夹中
				CopyF2D(*argv, argv[argc - 1]);
			else
				oops("file exist", argv[argc - 1]);//文件已存在
		}
	}
	return 0;
}
