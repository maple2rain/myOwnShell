#include "../inc/debug.h"

void oops(char *s1, char *s2)
{
	fprintf(stderr, "Error %s ", s1);
	perror(s2);
	exit(1);
}
