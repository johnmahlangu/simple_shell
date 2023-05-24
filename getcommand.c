#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include "main.h"

extern char **environ;

char *get_command_path(const char *command) {

	char *path_env;
	char *path;
	char *command_path = NULL;
	char *temp_path;

    	if (command[0] == '/') {
        	if (access(command, F_OK) == 0) {
            		return strdup(command);
        } 
	else {
            return NULL;
        }

    	}

   	path_env = _getenv("PATH");
    	path = strtok(path_env, ":");
    	command_path = NULL;

    	while (path != NULL) {

        temp_path = malloc(_strlen(path) + str_len(command) + 2);

        _sprintf(temp_path, "%s/%s", path, command);

        if (access(temp_path, F_OK) == 0) {
            command_path = temp_path;
            break;
        }

        free(temp_path);
        path = strtok(NULL, ":");
    }

    return command_path;
}
