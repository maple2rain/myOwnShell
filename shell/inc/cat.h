#ifndef _CAT_H
#define _CAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"

#define KB 1024


typedef enum status{
	TRUE, FALSE
}Status;

void doCat(FILE *fp);


#endif

