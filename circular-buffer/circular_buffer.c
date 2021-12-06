#include <stdio.h>
#include <stdlib.h>

#include "circular_buffer.h"

int validate(const struct circular_buffer_t *a)
{
    if (!a)
        return 0;

    if (!a->ptr)
        return 0;

    if (a->begin < 0 || a->end < 0 || a->capacity <= 0 || a->end >= a->capacity || a->begin >= a->capacity)
    {
        return 0;
    }

    return 1;
}

int circular_buffer_create(struct circular_buffer_t *a, int N)
{
    if (!a || N < 1)
        return 1;

    a->ptr = (int *)malloc(N * sizeof(int));

    if (!a->ptr)
        return 2;

    a->begin = 0;
    a->end = 0;
    a->capacity = N;
    a->full = 0;

    return 0;
}

int circular_buffer_create_struct(struct circular_buffer_t **cb, int N)
{
    if (!cb || N < 1)
        return 1;

    *cb = (struct circular_buffer_t *)malloc(sizeof(struct circular_buffer_t));

    if (!*cb)
        return 2;

    if (circular_buffer_create(*cb, N) == 2)
    {
        circular_buffer_destroy_struct(cb);
        return 2;
    }

    return 0;
}

void circular_buffer_destroy(struct circular_buffer_t *a)
{
    if (!a)
        return;

    free(a->ptr);
}

void circular_buffer_destroy_struct(struct circular_buffer_t **a)
{
    if (!a || !*a)
        return;

    circular_buffer_destroy(*a);

    free(*a);
}

int circular_buffer_push_back(struct circular_buffer_t *cb, int value)
{
    if (!validate(cb))
        return 1;

    if (circular_buffer_full(cb))
    {
        *(cb->ptr + cb->begin) = value;

        cb->begin = (cb->begin + 1) % cb->capacity;
        cb->end = (cb->end + 1) % cb->capacity;
    }
    else
    {
        *(cb->ptr + cb->end) = value;

        cb->end = (cb->end + 1) % cb->capacity;
    }

    if (cb->begin == cb->end)
        cb->full = 1;

    return 0;
}

int circular_buffer_pop_front(struct circular_buffer_t *a, int *err_code)
{
    if (!validate(a))
    {
        if (err_code)
            *err_code = 1;
        return 1;
    }

    if (circular_buffer_empty(a))
    {
        if (err_code)
            *err_code = 2;
        return 0;
    }

    int ret = *(a->ptr + a->begin);

    a->begin = (a->begin + 1) % a->capacity;

    if (a->begin == a->end)
    {
        a->begin = 0;
        a->end = 0;
    }

    if (err_code)
        *err_code = 0;

    a->full = 0;

    return ret;
}

int circular_buffer_pop_back(struct circular_buffer_t *a, int *err_code)
{
    if (!validate(a))
    {
        if (err_code)
            *err_code = 1;
        return 1;
    }

    if (circular_buffer_empty(a))
    {
        if (err_code)
            *err_code = 2;
        return 0;
    }

    a->end -= 1;
    if (a->end < 0)
        a->end = a->capacity - 1;

    int ret = *(a->ptr + a->end);

    if (a->begin == a->end)
    {
        a->begin = 0;
        a->end = 0;
    }

    if (err_code)
        *err_code = 0;

    a->full = 0;

    return ret;
}

int circular_buffer_empty(const struct circular_buffer_t *a)
{
    if (!validate(a))
        return -1;

    if (a->begin == a->end && !a->full)
        return 1;

    return 0;
}

int circular_buffer_full(const struct circular_buffer_t *a)
{
    if (!validate(a))
        return -1;

    return a->full;
}

void circular_buffer_display(const struct circular_buffer_t *a)
{
    if (!validate(a))
        return;

    if (circular_buffer_empty(a))
        return;

    int amount;

    if (circular_buffer_full(a))
        amount = a->capacity;
    else if (a->begin > a->end)
        amount = a->capacity - a->begin + a->end;
    else
        amount = a->end - a->begin;

    for (int i = 0; i < amount; i++)
    {
        int idx = (a->begin + i) % a->capacity;
        printf("%d ", *(a->ptr + idx));
    }
    printf("\n");
}