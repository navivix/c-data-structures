#include <stdio.h>

#include "circular_buffer.h"

int main(void)
{
    int cap;
    struct circular_buffer_t *buffer;

    printf("Podaj rozmiar bufora: ");

    if (!scanf("%d", &cap))
    {
        printf("Incorrect input");
        return 1;
    }

    if (cap < 1)
    {
        printf("Incorrect input data");
        return 2;
    }

    if (circular_buffer_create_struct(&buffer, cap) == 2)
    {
        printf("Failed to allocate memory");
        return 8;
    }

    while (1)
    {
        int choice;
        int temp;
        int code;

        printf("Co chcesz zrobic? ");

        if (!scanf("%d", &choice))
        {
            printf("Incorrect input");
            circular_buffer_destroy_struct(&buffer);
            return 1;
        }

        if (choice == 0)
            break;

        else if (choice == 1)
        {
            printf("Podaj liczbe: ");

            if (!scanf("%d", &temp))
            {
                printf("Incorrect input");
                circular_buffer_destroy_struct(&buffer);
                return 1;
            }

            circular_buffer_push_back(buffer, temp);
        }

        else if (choice == 2)
        {
            temp = circular_buffer_pop_back(buffer, &code);

            if (code == 2)
                printf("Buffer is empty\n");
            else
                printf("%d\n", temp);
        }

        else if (choice == 3)
        {
            temp = circular_buffer_pop_front(buffer, &code);

            if (code == 2)
                printf("Buffer is empty\n");
            else
                printf("%d\n", temp);
        }

        else if (choice == 4)
        {
            if (circular_buffer_empty(buffer))
                printf("Buffer is empty\n");
            else
                circular_buffer_display(buffer);
        }

        else if (choice == 5)
        {
            printf("%d\n", circular_buffer_empty(buffer));
        }

        else if (choice == 6)
        {
            printf("%d\n", circular_buffer_full(buffer));
        }

        else
            printf("Incorrect input data\n");
    }

    circular_buffer_destroy_struct(&buffer);

    return 0;
}