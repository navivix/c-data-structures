#include <stdio.h>

#include "stack.h"

int main(int argc, char *argv[])
{
    argc--, argv++;

    if (argc < 1)
        return printf("Not enough arguments"), 9;

    for (int i = 0; i < argc; i++)
    {
        struct stack_t *stack = NULL;
        int code = stack_load(&stack, *(argv + i));
        if (code == 2)
        {
            printf("Couldn't open file %s\n", *(argv + i));
            continue;
        }
        if (code == 3)
            return printf("Failed to allocate memory"), 8;
        code = stack_save(stack, *(argv + i));
        if (code == 2)
            return printf("Couldn't create file"), stack_destroy(&stack), 5;
        stack_destroy(&stack);
        printf("File %s saved\n", *(argv + i));
    }

    stack_pop(NULL, NULL);

    return 0;
}