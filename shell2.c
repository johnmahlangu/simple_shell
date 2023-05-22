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
    char *path_env = _getenv("PATH");
    char *path = strtok(path_env, ":");
    char *command_path = NULL;

    while (path != NULL) {
        char *temp_path = malloc(strlen(path) + strlen(command) + 2);
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

int main(int argc, char *argv[]) {
    char *command = NULL;
    size_t command_length = 0;
    ssize_t n;
    int status;
    char *delim = " \n";
    unsigned int maxArg = 12;
    char *args[maxArg];
    int num_args = 0;

    while (1) {
        printf("#cisfun$ ");
        fflush(stdout);

        n = getline(&command, &command_length, stdin);

        if (n == -1) {
            break;
        }

        char *token = strtok(command, delim);

        num_args = 0;

        while (token != NULL && num_args < maxArg - 1) {
            args[num_args] = token;
            num_args++;
            token = strtok(NULL, delim);
        }

        args[num_args] = NULL;

        if (num_args == 0) {
            continue;  // No command provided, continue to the next iteration
        }

        char *command_path = get_command_path(args[0]);

        if (command_path == NULL) {
            printf("Command not found: %s\n", args[0]);
            continue;  // Command doesn't exist, continue to the next iteration
        }

        pid_t pid = fork();

        if (pid == -1) {
            perror("Unsuccessful");
            free(command_path);
            exit(1);
        } else if (pid == 0) {
            if (argc > 1) {
                // Concatenate additional command line arguments with the existing ones
                int i;
                for (i = 0; i < argc - 1 && num_args < maxArg - 1; i++) {
                    args[num_args] = argv[i + 1];
                    num_args++;
                }
            }

            execve(command_path, args, environ);

            perror(args[0]);
            free(command_path);
            exit(1);
        } else {
            waitpid(pid, &status, 0);
            free(command_path);
        }

        // Restore the original PATH
        setenv("PATH", "/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin", 1);
    }

    free(command);

    return 0;
}
