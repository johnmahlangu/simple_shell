#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdarg.h>
#include "main.h"

int _sprintf(char *str, const char *format, ...) {
	int saved_stdout;
	va_list args;
	int count = 0;
	char ch;
	
    int fd = open("/dev/null", O_WRONLY);
    if (fd == -1) {
        return -1;
    }

    saved_stdout = dup(STDOUT_FILENO);
    if (saved_stdout == -1) {
        close(fd);
        return -1;
    }

    if (dup2(fd, STDOUT_FILENO) == -1) {
        close(fd);
        close(saved_stdout);
        return -1;
    }

    va_start(args, format);

    while ((ch = *format++) != '\0') {
        if (ch == '%') {
            ch = *format++;
            switch (ch) {
                case 'd':
                case 'i': {
                    int num = va_arg(args, int);
                    char buffer[32];
                    int len = 0;
                    if (num < 0) {
                        buffer[len++] = '-';
                        num = -num;
                    }
                    do {
                        buffer[len++] = '0' + num % 10;
                        num /= 10;
                    } while (num > 0);
                    while (len > 0) {
                        str[count++] = buffer[--len];
                    }
                    break;
                }
                case 's': {
                    const char *str_arg = va_arg(args, const char *);
                    while (*str_arg != '\0') {
                        str[count++] = *str_arg++;
                    }
                    break;
                }
                default:
                    str[count++] = ch;
                    break;
            }
        } else {
            str[count++] = ch;
        }
    }

    va_end(args);

    if (dup2(saved_stdout, STDOUT_FILENO) == -1) {
        close(fd);
        close(saved_stdout);
        return -1;
    }

    close(fd);
    close(saved_stdout);

    return count;
}
