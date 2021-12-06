#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "stack.h"

int stack_push(struct stack_t **stack, char *value)
{
    if (!stack || !value)
        return 1;

    struct stack_t *next = malloc(sizeof(*next));

    if (!next)
        return 2;

    next->sentence = value;
    next->prev = *stack ? *stack : NULL;

    *stack = next;

    return 0;
}

char *stack_pop(struct stack_t **stack, int *err_code)
{
    if (!stack || !*stack)
    {
        if (err_code)
            *err_code = 1;
        return NULL;
    }

    struct stack_t *prev = (*stack)->prev;
    char *sent = (*stack)->sentence;

    free(*stack);

    *stack = prev;

    if (err_code)
        *err_code = 0;

    return sent;
}

void stack_destroy(struct stack_t **stack)
{
    if (!stack)
        return;
    while (*stack)
    {
        if ((*stack)->sentence)
            free((*stack)->sentence);
        struct stack_t *prev = (*stack)->prev;
        free(*stack);
        *stack = prev;
    }
}

int stack_load(struct stack_t **stack, const char *filename)
{
    if (!stack || *stack || !filename)
        return 1;

    FILE *fptr = fopen(filename, "rt");

    if (!fptr)
        return 2;

    int start = 0;
    int len = 0;

    while (1)
    {
        int c = fgetc(fptr);
        if (c == EOF)
            break;
        len++;
        if (c == '.')
        {
            char *sent = calloc(len + 1, 1);
            if (!sent)
                return fclose(fptr), stack_destroy(stack), 3;
            fseek(fptr, start, SEEK_SET);
            for (int i = 0; i < len; i++)
            {
                char ch = fgetc(fptr);
                strncat(sent, &ch, 1);
            }
            start += len;
            len = 0;
            if (stack_push(stack, sent) == 2)
                return fclose(fptr), free(sent), stack_destroy(stack), 3;
        }
    }

    fclose(fptr);

    return 0;
}

int stack_save(const struct stack_t *stack, const char *filename)
{
    if (!stack || !filename)
        return 1;

    FILE *fptr = fopen(filename, "wt");

    if (!fptr)
        return 2;

    const struct stack_t *temp = stack;

    while (temp)
    {
        char *sent = temp->sentence;
        fprintf(fptr, "%s", sent);
        if (ferror(fptr))
            return fclose(fptr), 2;
        temp = temp->prev;
    }

    fclose(fptr);

    return 0;
}