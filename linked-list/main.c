#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

int main()
{
    struct linked_list_t *ll = ll_create();

    if (!ll)
        return printf("Failed to allocate memory"), 8;

    while (1)
    {
        int choice = -1;
        int val;
        int idx;
        int code = -1;

        printf("Co chcesz zrobic? ");

        if (scanf("%d", &choice) != 1)
            return printf("Incorrect input"), ll_clear(ll), free(ll), 1;

        if (choice < 0 || choice > 13)
        {
            printf("Incorrect input data\n");
            continue;
        }

        if (choice == 0)
            break;

        if (choice == 1)
        {
            printf("Podaj liczbe: ");
            if (scanf("%d", &val) != 1)
                return printf("Incorrect input"), ll_clear(ll), free(ll), 1;
            if (ll_push_back(ll, val) == 2)
                return printf("Failed to allocate memory"), ll_clear(ll), free(ll), 8;
        }

        if (choice == 2)
            ll_is_empty(ll) ? printf("List is empty\n") : printf("%d\n", ll_pop_back(ll, NULL));

        if (choice == 3)
        {
            printf("Podaj liczbe: ");
            if (scanf("%d", &val) != 1)
                return printf("Incorrect input"), ll_clear(ll), free(ll), 1;
            if (ll_push_front(ll, val) == 2)
                return printf("Failed to allocate memory"), ll_clear(ll), free(ll), 8;
        }

        if (choice == 4)
            ll_is_empty(ll) ? printf("List is empty\n") : printf("%d\n", ll_pop_front(ll, NULL));

        if (choice == 5)
        {
            printf("Podaj liczbe: ");
            if (scanf("%d", &val) != 1)
                return printf("Incorrect input"), ll_clear(ll), free(ll), 1;
            printf("Podaj index: ");
            if (scanf("%d", &idx) != 1)
                return printf("Incorrect input"), ll_clear(ll), free(ll), 1;
            code = ll_insert(ll, idx, val);
            if (code == 1)
                printf("Index out of range\n");
            if (code == 2)
                return printf("Failed to allocate memory"), ll_clear(ll), free(ll), 8;
        }

        if (choice == 6)
        {
            if (ll_is_empty(ll))
                printf("List is empty\n");
            else
            {
                printf("Podaj index: ");
                if (scanf("%d", &idx) != 1)
                    return printf("Incorrect input"), ll_clear(ll), free(ll), 1;
                val = ll_remove(ll, idx, &code);
                if (code == 2)
                    return printf("Failed to allocate memory"), ll_clear(ll), free(ll), 8;
                if (code == 1)
                    printf("Index out of range\n");
                else
                    printf("%d\n", val);
            }
        }

        if (choice == 7)
            ll_is_empty(ll) ? printf("List is empty\n") : printf("%d\n", ll_back(ll, NULL));

        if (choice == 8)
            ll_is_empty(ll) ? printf("List is empty\n") : printf("%d\n", ll_front(ll, NULL));

        if (choice == 9)
            printf("%d\n", ll_is_empty(ll));

        if (choice == 10)
            printf("%d\n", ll_size(ll));

        if (choice == 11)
            ll_clear(ll);

        if (choice == 12)
        {
            if (ll_is_empty(ll))
                printf("List is empty\n");
            else
            {
                printf("Podaj index: ");
                if (scanf("%d", &idx) != 1)
                    return printf("Incorrect input"), ll_clear(ll), free(ll), 1;
                val = ll_at(ll, idx, &code);
                code == 1 ? printf("Index out of range\n") : printf("%d\n", val);
            }
        }

        if (choice == 13)
            ll_is_empty(ll) ? printf("List is empty\n") : (ll_display(ll), printf("\n"));
    }

    ll_clear(ll);
    free(ll);

    return 0;
}