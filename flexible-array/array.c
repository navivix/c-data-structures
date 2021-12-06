#include <stdio.h>
#include <stdlib.h>

#include "array.h"

int validate(const struct array_t *a)
{
    if (!a)
        return 0;
    if (!a->ptr || a->size < 0 || a->capacity < 1 || a->size > a->capacity)
        return 0;
    return 1;
}

int array_create(struct array_t *a, int N)
{
    if (!a || N < 1)
        return 1;

    a->ptr = (int *)malloc(N * sizeof(int));

    if (!a->ptr)
        return 2;

    a->size = 0;
    a->capacity = N;

    return 0;
}

int array_create_struct(struct array_t **a, int N)
{
    if (!a || N < 1)
        return 1;

    *a = (struct array_t *)malloc(sizeof(struct array_t));

    if (!*a)
        return 2;

    if (array_create(*a, N) == 2)
    {
        free(*a);
        return 2;
    }

    return 0;
}

int array_push_back(struct array_t *a, int value)
{
    if (!validate(a))
        return 1;

    if (a->size == a->capacity)
    {
        int *new = (int *)realloc(a->ptr, 2 * a->capacity * sizeof(int));

        if (!new)
            return 2;

        a->ptr = new;
        a->capacity *= 2;
    }

    *(a->ptr + a->size) = value;
    a->size += 1;

    return 0;
}

int array_remove_item(struct array_t *a, int value)
{
    if (!validate(a))
        return -1;

    int removed = 0;

    for (int i = 0; i < a->size - removed; i++)
    {
        if (*(a->ptr + i) == value)
        {
            for (int j = i + 1; j < a->size; j++)
            {
                *(a->ptr + j - 1) = *(a->ptr + j);
            }
            removed++;
            i--;
        }
    }

    a->size -= removed;

    if (a->size * 4 < a->capacity)
    {
        int new_size = a->capacity / 2 + (a->capacity / 2 == 0 ? 1 : 0);
        int *new = (int *)realloc(a->ptr, new_size * sizeof(int));

        if (!new)
            return removed;

        a->ptr = new;
        a->capacity = new_size;
    }

    return removed;
}

void array_display(const struct array_t *a)
{
    if (!validate(a))
        return;

    for (int i = 0; i < a->size; i++)
    {
        printf("%d ", *(a->ptr + i));
    }
}

void array_destroy(struct array_t *a)
{
    if (!a || !a->ptr)
        return;

    free(a->ptr);
}

void array_destroy_struct(struct array_t **a)
{
    if (!a)
        return;

    array_destroy(*a);

    free(*a);
}