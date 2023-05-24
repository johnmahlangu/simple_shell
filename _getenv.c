#include "main.h"
#include <stdio.h>
#include <string.h>

extern char **environ;

char *_getenv(const char *name) {
    char **env = environ;
    while (*env != NULL) {
        char *env_var = *env;
        int len = str_len(name);

        if (_strncmp(env_var, name, len) == 0 && env_var[len] == '=') {
            return &env_var[len + 1];
        }

        env++;
    }

    return NULL;
}
