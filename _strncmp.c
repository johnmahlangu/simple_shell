#include "main.h"
#include <stdio.h>

int _strncmp(const char *str1, const char *str2, size_t n) {
	size_t i;

    for (i = 0; i < n; i++) {
        if (str1[i] != str2[i])
            return (int)(unsigned char)str1[i] - (int)(unsigned char)str2[i];

        if (str1[i] == '\0')
            break;
    }

    return 0;
}
