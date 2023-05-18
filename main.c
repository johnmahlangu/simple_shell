#include "main.h"

/**
 * main - main function
 * return: 0
*/

int main(int argc, char **argv)
{
    char *prompt = "$ ";
    char *line = NULL, *line_copy = NULL;
    size_t len = 0;
    ssize_t num_char;
    char *delimt = " \n";
    char *token;
    int i;
    int nums_tokens = 0;
    (void)argc;
    while (1)
    {
        printf("%s", prompt);

        num_char = getline(&line, &len, stdin);
        if (num_char == -1)
        {
            return (-1);
        }

        line_copy = malloc(sizeof(char) * num_char);
        if (line_copy == NULL)
        {
            perror("error memory");
            return (-1);
        }

        strcpy(line_copy, line);

        token = strtok(line, delimt);

        while (token != NULL){
            nums_tokens++;
            token = strtok(NULL, delimt);
        }
        nums_tokens++;

        argv = malloc(sizeof(char *) * nums_tokens);

        token = strtok(line_copy, delimt);
        
        for (i = 0; token != NULL; i++)
        {
            argv[i] = malloc(sizeof(char) * strlen(token));
            strcpy(argv[i], token);
            token = strtok(NULL, delimt);
        }
        argv[i] = NULL;

        /*printf("%s\n", line);*/
        execmd(argv);
    }
    free(line);
    free(line_copy);
    free(argv);
    return (0);
}