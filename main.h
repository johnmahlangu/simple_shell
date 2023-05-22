#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


typedef struct list
{
	char *string;
	int number;
	struct list *next;
}list_t;

typedef struct info
{
	list_t *envi;
	list_t **environ;
}info_t;
char *starts(const char *strsearch, const char *strfind);
void execmd(char **argv);
char *_getenv(const char *name);
#endif
