#include <stdio.h>
#include "main.h"
#include <string.h>

char *_getenv(const char *name) {
    extern char **environ;
    char *env_var;
    size_t name_length = strlen(name);

    for (char **env = environ; *env != NULL; env++) {
        env_var = *env;

        if (strncmp(env_var, name, name_length) == 0 && env_var[name_length] == '=') {
            return &env_var[name_length + 1];
        }
    }

    return NULL;  // Environment variable not found
}
