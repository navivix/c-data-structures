#include <stdio.h>
#include <stdlib.h>

#include "doubly_linked_list.h"

struct doubly_linked_list_t *dll_create()
{
    return calloc(1, sizeof(struct doubly_linked_list_t));
}

int dll_push_back(struct doubly_linked_list_t *dll, int value)
{
    if (!dll)
        return 1;
    struct node_t *node = calloc(1, sizeof *node);
    if (!node)
        return 2;
    node->data = value;
    node->next = NULL;
    node->prev = NULL;
    if (dll_is_empty(dll))
    {
        dll->head = node;
        dll->tail = node;
    }
    else
    {
        dll_end(dll)->next = node;
        node->prev = dll_end(dll);
        dll->tail = node;
    }
    return 0;
}
int dll_push_front(struct doubly_linked_list_t *dll, int value)
{
    if (!dll)
        return 1;
    struct node_t *node = calloc(1, sizeof *node);
    if (!node)
        return 2;
    node->data = value;
    node->next = NULL;
    node->prev = NULL;
    if (dll_is_empty(dll))
    {
        dll->head = node;
        dll->tail = node;
    }
    else
    {
        node->next = dll_begin(dll);
        dll_begin(dll)->prev = node;
        dll->head = node;
    }
    return 0;
}
int dll_pop_front(struct doubly_linked_list_t *dll, int *err_code)
{
    if (!dll || dll_is_empty(dll))
    {
        if (err_code)
            *err_code = 1;
        return 0;
    }
    int pop = dll_begin(dll)->data;
    struct node_t *node = dll_begin(dll);
    if (dll->tail == dll->head)
    {
        dll->tail = NULL;
        dll->head = NULL;
    }
    else
    {
        dll->head->next->prev = NULL;
        dll->head = node->next;
    }
    free(node);
    if (err_code)
        *err_code = 0;
    return pop;
}
int dll_pop_back(struct doubly_linked_list_t *dll, int *err_code)
{
    if (!dll || dll_is_empty(dll))
    {
        if (err_code)
            *err_code = 1;
        return 0;
    }
    int pop = dll_end(dll)->data;
    struct node_t *node = dll_end(dll);
    if (dll_begin(dll) == dll_end(dll))
    {
        dll->tail = NULL;
        dll->head = NULL;
    }
    else
    {
        node->prev->next = NULL;
        dll->tail = node->prev;
    }
    free(node);
    if (err_code)
        *err_code = 0;
    return pop;
}

int dll_back(const struct doubly_linked_list_t *dll, int *err_code)
{
    if (!dll || dll_is_empty(dll))
    {
        if (err_code)
            *err_code = 1;
        return 0;
    }
    if (err_code)
        *err_code = 0;
    return dll->tail->data;
}
int dll_front(const struct doubly_linked_list_t *dll, int *err_code)
{
    if (!dll || dll_is_empty(dll))
    {
        if (err_code)
            *err_code = 1;
        return 0;
    }
    if (err_code)
        *err_code = 0;
    return dll->head->data;
}

struct node_t *dll_begin(struct doubly_linked_list_t *dll)
{
    if (!dll)
        return NULL;
    return dll->head;
}
struct node_t *dll_end(struct doubly_linked_list_t *dll)
{
    if (!dll)
        return NULL;
    return dll->tail;
}

int dll_size(const struct doubly_linked_list_t *dll)
{
    if (!dll)
        return -1;
    if (dll_is_empty(dll))
        return 0;
    int count = 0;
    struct node_t *node = dll->head;
    while (node)
        count++, node = node->next;
    return count;
}
int dll_is_empty(const struct doubly_linked_list_t *dll)
{
    if (!dll)
        return -1;
    if (!dll->tail && !dll->head)
        return 1;
    return 0;
}

int dll_at(const struct doubly_linked_list_t *dll, unsigned int index, int *err_code)
{
    if (!dll || index >= (unsigned int)dll_size(dll))
    {
        if (err_code)
            *err_code = 1;
        return 0;
    }
    struct node_t *node = dll->head;
    while (index)
        index--, node = node->next;
    if (err_code)
        *err_code = 0;
    return node->data;
}

int dll_insert(struct doubly_linked_list_t *dll, unsigned int index, int value)
{
    if (!dll || index > (unsigned int)dll_size(dll))
        return 1;
    struct node_t *node = calloc(1, sizeof(*node));
    if (!node)
        return 2;
    node->data = value;
    node->next = NULL;
    node->prev = NULL;
    if (dll_is_empty(dll))
    {
        dll->tail = node;
        dll->head = node;
    }
    else
    {
        struct node_t *curr = dll->head;
        while (index)
        {
            curr = curr->next;
            index--;
        }
        node->next = curr;
        if (curr == NULL)
        {
            dll->tail->next = node;
            node->prev = dll->tail;
            dll->tail = node;
        }
        else if (curr == dll_begin(dll))
        {
            curr->prev = node;
            dll->head = node;
        }
        else
        {
            node->prev = curr->prev;
            curr->prev->next = node;
            curr->prev = node;
        }
    }
    return 0;
}
int dll_remove(struct doubly_linked_list_t *dll, unsigned int index, int *err_code)
{
    if (!dll || dll_is_empty(dll) || index >= (unsigned int)dll_size(dll))
    {
        if (err_code)
            *err_code = 1;
        return 0;
    }
    struct node_t *curr = dll->head;
    int pop;
    while (index)
    {
        curr = curr->next;
        index--;
    }
    pop = curr->data;
    if (dll_begin(dll) == dll_end(dll))
    {
        dll->tail = NULL;
        dll->head = NULL;
    }
    else
    {
        if (curr == dll_begin(dll))
        {
            dll->head = curr->next;
            curr->next->prev = NULL;
        }
        else if (curr == dll_end(dll))
        {
            dll->tail = curr->prev;
            curr->prev->next = NULL;
        }
        else
        {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
        }
    }
    free(curr);
    if (err_code)
        *err_code = 0;
    return pop;
}

void dll_clear(struct doubly_linked_list_t *dll)
{
    if (!dll)
        return;
    struct node_t *node = dll_begin(dll);
    while (node)
    {
        struct node_t *next = node->next;
        free(node);
        node = next;
    }
    dll->head = NULL;
    dll->tail = NULL;
}

void dll_display(const struct doubly_linked_list_t *dll)
{
    if (!dll)
        return;
    struct node_t *node = dll->head;
    while (node)
    {
        printf("%d ", node->data);
        node = node->next;
    }
}
void dll_display_reverse(const struct doubly_linked_list_t *dll)
{
    if (!dll)
        return;
    struct node_t *node = dll->tail;
    while (node)
    {
        printf("%d ", node->data);
        node = node->prev;
    }
}
