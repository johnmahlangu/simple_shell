#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

extern char **environ;

int _putenv(const char *string) {
	char *name, **env, **new_env;
	const char *equal_sign;
	size_t name_len = 0;

    	if (string == NULL || _strchr(string, '=') == NULL)
        	return -1;

    	name = strdup(string);
    	if (name == NULL)
        	return -1;

    	equal_sign = _strchr(name, '=');
    	name_len = equal_sign - name;

    	env = environ;
    	while (*env != NULL) {
        	if (_strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=') {
            	free(*env);
            	*env = strdup(string);
            	free(name);
            	if (*env == NULL)
                	return -1;
            return 0;
        }
        env++;
    }

    	new_env = (char **)realloc(environ, (env - environ + 2) * sizeof(char *));
    	if (new_env == NULL) {
        	free(name);
        	return -1;
    	}
    	environ = new_env;
    	environ[env - environ] = strdup(string);
    	environ[env - environ + 1] = NULL;

    	free(name);
    	return 0;
}
