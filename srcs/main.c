#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h> 

int main() 
{
    char *input;

    while (1) 
    {
        input = readline("ms$> ");
        if (input == NULL) {
            break;
        }
        add_history(input);
        free(input);
    }
    printf("Shell finished\n");
    return 0;
}