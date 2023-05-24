#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int _setenv(const char *name, const char *value, int overwrite) {
	int name_len = 0, result = 0;
	int value_len = 0;
	char *env_var, *new_env_var;

    	if (name == NULL || value == NULL)
        	return -1;

    	name_len = str_len(name);
    	value_len = str_len(value);

    	env_var = _getenv(name);

    	if (env_var != NULL && !overwrite)
        	return 0;

    	new_env_var = (char *)malloc(name_len + value_len + 2);

    	if (new_env_var == NULL)
        	return -1;

    	_sprintf(new_env_var, "%s=%s", name, value);

    	result = _putenv(new_env_var);

    	if (result != 0)
        	return -1;

    return 0;
}
