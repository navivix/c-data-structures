#include <stdlib.h>
#include <stdio.h>

#include "linked_list.h"

struct linked_list_t *ll_create()
{
    return calloc(1, sizeof(struct linked_list_t));
}

int ll_push_back(struct linked_list_t *ll, int value)
{
    if (!ll)
        return 1;
    struct node_t *node = calloc(1, sizeof *node);
    if (!node)
        return 2;
    node->data = value;
    node->next = NULL;
    if (ll_is_empty(ll))
    {
        ll->head = node;
        ll->tail = node;
    }
    else
    {
        ll_end(ll)->next = node;
        ll->tail = node;
    }
    return 0;
}
int ll_push_front(struct linked_list_t *ll, int value)
{
    if (!ll)
        return 1;
    struct node_t *node = calloc(1, sizeof *node);
    if (!node)
        return 2;
    node->data = value;
    node->next = NULL;
    if (ll_is_empty(ll))
    {
        ll->head = node;
        ll->tail = node;
    }
    else
    {
        node->next = ll_begin(ll);
        ll->head = node;
    }
    return 0;
}
int ll_pop_front(struct linked_list_t *ll, int *err_code)
{
    if (!ll || ll_is_empty(ll))
    {
        if (err_code)
            *err_code = 1;
        return 0;
    }
    int pop = ll_begin(ll)->data;
    struct node_t *node = ll_begin(ll);
    if (ll->tail == ll->head)
    {
        ll->tail = NULL;
        ll->head = NULL;
    }
    ll->head = node->next;
    free(node);
    if (err_code)
        *err_code = 0;
    return pop;
}
int ll_pop_back(struct linked_list_t *ll, int *err_code)
{
    if (!ll || ll_is_empty(ll))
    {
        if (err_code)
            *err_code = 1;
        return 0;
    }
    int pop = ll_end(ll)->data;
    struct node_t *node = ll_end(ll);
    struct node_t *curr = ll_begin(ll);
    if (curr == node)
    {
        curr = NULL;
        ll->tail = NULL;
        ll->head = NULL;
    }
    else
    {
        while (curr->next != node)
            curr = curr->next;
    }
    if (curr)
        curr->next = NULL;
    ll->tail = curr;
    free(node);
    if (err_code)
        *err_code = 0;
    return pop;
}

int ll_back(const struct linked_list_t *ll, int *err_code)
{
    if (!ll || ll_is_empty(ll))
    {
        if (err_code)
            *err_code = 1;
        return 0;
    }
    if (err_code)
        *err_code = 0;
    return ll->tail->data;
}
int ll_front(const struct linked_list_t *ll, int *err_code)
{
    if (!ll || ll_is_empty(ll))
    {
        if (err_code)
            *err_code = 1;
        return 0;
    }
    if (err_code)
        *err_code = 0;
    return ll->head->data;
}

struct node_t *ll_begin(struct linked_list_t *ll)
{
    if (!ll)
        return NULL;
    return ll->head;
}
struct node_t *ll_end(struct linked_list_t *ll)
{
    if (!ll)
        return NULL;
    return ll->tail;
}

int ll_size(const struct linked_list_t *ll)
{
    if (!ll)
        return -1;
    if (ll_is_empty(ll))
        return 0;
    int count = 0;
    struct node_t *node = ll->head;
    while (node)
        count++, node = node->next;
    return count;
}
int ll_is_empty(const struct linked_list_t *ll)
{
    if (!ll)
        return -1;
    if (!ll->tail && !ll->head)
        return 1;
    return 0;
}
int ll_at(const struct linked_list_t *ll, unsigned int index, int *err_code)
{
    if (!ll || index >= (unsigned int)ll_size(ll))
    {
        if (err_code)
            *err_code = 1;
        return 0;
    }
    struct node_t *node = ll->head;
    while (index)
        index--, node = node->next;
    if (err_code)
        *err_code = 0;
    return node->data;
}

int ll_insert(struct linked_list_t *ll, unsigned int index, int value)
{
    if (!ll || index > (unsigned int)ll_size(ll))
        return 1;
    struct node_t *node = calloc(1, sizeof(*node));
    if (!node)
        return 2;
    node->data = value;
    node->next = NULL;
    if (ll_is_empty(ll))
    {
        ll->tail = node;
        ll->head = node;
    }
    else
    {
        struct node_t *prev = NULL;
        struct node_t *curr = ll->head;
        while (index)
        {
            if (index == 1)
                prev = curr;
            curr = curr->next;
            index--;
        }
        if (curr == ll_begin(ll))
            ll->head = node;
        if (curr == NULL)
            ll->tail = node;
        if (prev)
            prev->next = node;
        node->next = curr;
    }
    return 0;
}

int ll_remove(struct linked_list_t *ll, unsigned int index, int *err_code)
{
    if (!ll || ll_is_empty(ll) || index >= (unsigned int)ll_size(ll))
    {
        if (err_code)
            *err_code = 1;
        return 0;
    }
    struct node_t *prev = NULL;
    struct node_t *curr = ll->head;
    int pop;
    while (index)
    {
        if (index == 1)
            prev = curr;
        curr = curr->next;
        index--;
    }
    pop = curr->data;
    if (ll_begin(ll) == ll_end(ll))
    {
        ll->tail = NULL;
        ll->head = NULL;
    }
    else
    {
        if (curr == ll_begin(ll))
        {
            ll->head = curr->next;
        }
        else if (curr == ll_end(ll))
        {
            ll->tail = prev;
            prev->next = NULL;
        }
        else
        {
            prev->next = curr->next;
        }
    }
    free(curr);
    if (err_code)
        *err_code = 0;
    return pop;
}

void ll_clear(struct linked_list_t *ll)
{
    if (!ll)
        return;
    struct node_t *node = ll_begin(ll);
    while (node)
    {
        struct node_t *next = node->next;
        free(node);
        node = next;
    }
    ll->head = NULL;
    ll->tail = NULL;
}

void ll_display(const struct linked_list_t *ll)
{
    if (!ll)
        return;
    struct node_t *node = ll->head;
    while (node)
    {
        printf("%d ", node->data);
        node = node->next;
    }
}