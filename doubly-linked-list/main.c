#include <stdio.h>
#include <stdlib.h>

#include "doubly_linked_list.h"

int main()
{
    struct doubly_linked_list_t *dll = dll_create();

    if (!dll)
        return printf("Failed to allocate memory"), 8;

    while (1)
    {
        int choice = -1;
        int val;
        int idx;
        int code = -1;

        printf("Co chcesz zrobic? ");

        if (scanf("%d", &choice) != 1)
            return printf("Incorrect input"), dll_clear(dll), free(dll), 1;

        if (choice < 0 || choice > 14)
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
                return printf("Incorrect input"), dll_clear(dll), free(dll), 1;
            if (dll_push_back(dll, val) == 2)
                return printf("Failed to allocate memory"), dll_clear(dll), free(dll), 8;
        }

        if (choice == 2)
            dll_is_empty(dll) ? printf("List is empty\n") : printf("%d\n", dll_pop_back(dll, NULL));

        if (choice == 3)
        {
            printf("Podaj liczbe: ");
            if (scanf("%d", &val) != 1)
                return printf("Incorrect input"), dll_clear(dll), free(dll), 1;
            if (dll_push_front(dll, val) == 2)
                return printf("Failed to allocate memory"), dll_clear(dll), free(dll), 8;
        }

        if (choice == 4)
            dll_is_empty(dll) ? printf("List is empty\n") : printf("%d\n", dll_pop_front(dll, NULL));

        if (choice == 5)
        {
            printf("Podaj liczbe: ");
            if (scanf("%d", &val) != 1)
                return printf("Incorrect input"), dll_clear(dll), free(dll), 1;
            printf("Podaj index: ");
            if (scanf("%d", &idx) != 1)
                return printf("Incorrect input"), dll_clear(dll), free(dll), 1;
            code = dll_insert(dll, idx, val);
            if (code == 1)
                printf("Index out of range\n");
            if (code == 2)
                return printf("Failed to allocate memory"), dll_clear(dll), free(dll), 8;
        }

        if (choice == 6)
        {
            if (dll_is_empty(dll))
                printf("List is empty\n");
            else
            {
                printf("Podaj index: ");
                if (scanf("%d", &idx) != 1)
                    return printf("Incorrect input"), dll_clear(dll), free(dll), 1;
                val = dll_remove(dll, idx, &code);
                if (code == 2)
                    return printf("Failed to allocate memory"), dll_clear(dll), free(dll), 8;
                if (code == 1)
                    printf("Index out of range\n");
                else
                    printf("%d\n", val);
            }
        }

        if (choice == 7)
            dll_is_empty(dll) ? printf("List is empty\n") : printf("%d\n", dll_back(dll, NULL));

        if (choice == 8)
            dll_is_empty(dll) ? printf("List is empty\n") : printf("%d\n", dll_front(dll, NULL));

        if (choice == 9)
            printf("%d\n", dll_is_empty(dll));

        if (choice == 10)
            printf("%d\n", dll_size(dll));

        if (choice == 11)
            dll_clear(dll);

        if (choice == 12)
        {
            if (dll_is_empty(dll))
                printf("List is empty\n");
            else
            {
                printf("Podaj index: ");
                if (scanf("%d", &idx) != 1)
                    return printf("Incorrect input"), dll_clear(dll), free(dll), 1;
                val = dll_at(dll, idx, &code);
                code == 1 ? printf("Index out of range\n") : printf("%d\n", val);
            }
        }

        if (choice == 13)
            dll_is_empty(dll) ? printf("List is empty\n") : (dll_display(dll), printf("\n"));

        if (choice == 14)
            dll_is_empty(dll) ? printf("List is empty\n") : (dll_display_reverse(dll), printf("\n"));
    }

    dll_clear(dll);
    free(dll);

    return 0;
}