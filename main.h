#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdarg.h>

char *_getenv(const char *name);
const char *_strchr(const char *s, char c);
int _printf(const char *format, ...);
int _setenv(const char *name, const char *value, int overwrite);
char *str_chr(char *s, char c);
int _strcmp(char *s1, char *s2);
int _sprintf(char *str, const char *format, ...);
char *get_command_path(const char *command);
int str_len(const char *s);
int _strncmp(const char *str1, const char *str2, size_t n);
int _putenv(const char *string);
int _strlen(char *s);
#endif
