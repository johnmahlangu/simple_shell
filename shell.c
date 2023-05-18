#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

extern char **environ;

int main(void) {

    	char *command = NULL;
    	size_t command_length = 0;
	ssize_t n;
    	int status;
	char *delim = " \n";
	unsigned int maxArg = 12;
	char *args[maxArg];
	int num_args = 0;

    	while (1) 
	{
		printf("#cisfun$ ");
        	fflush(stdout);

        	n = getline(&command, &command_length, stdin);

        	if (n == -1) 
		{
            		break;
        	}

        	char *token = strtok(command, delim);
        	while (token != NULL && num_args <maxArg - 1) 
		{
            		args[num_args] = token;
            		num_args++;
            		token = strtok(NULL, delim);
        	}

        	args[num_args] = NULL;

        	pid_t pid = fork();

        	if (pid == -1) 
		{
            		perror("Unsuccessful");
            		 exit(1);
        	} 
		else if (pid == 0) 
		{
            		execve(args[0], args, environ);

            		perror(args[0]);
            			exit(1);
        	} 
		else 
		{
            		waitpid(pid, &status, 0);
        	}
    	}

    	free(command);

    	return (0);
}
