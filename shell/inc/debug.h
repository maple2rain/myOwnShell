#ifndef _DEBUG_H
#define _DEBUG_H

#include <stdio.h>
#include <stdlib.h>

#define DEBUG_ON 1

#if DEBUG_ON
	#define DEBUG_PRINT(format,args...) printf(format,##args)
#else
	#define DEBUG_PRINT(format,args...)
#endif

void oops(char *s1, char *s2);


#endif
