#include <stdio.h>

#include "array.h"

int main(void)
{
    struct array_t *arr;
    int n;

    printf("Podaj rozmiar: ");

    if (!scanf("%d", &n))
    {
        printf("Incorrect input");
        return 1;
    }

    if (n < 1)
    {
        printf("Incorrect input data");
        return 2;
    }

    if (array_create_struct(&arr, n) == 2)
    {
        printf("Failed to allocate memory");
        return 8;
    }

    while (1)
    {
        int choice;
        int temp;

        printf("Co chcesz zrobic? ");

        if (!scanf("%d", &choice))
        {
            printf("Incorrect input");
            array_destroy_struct(&arr);
            return 1;
        }

        if (choice == 0)
            break;

        else if (choice == 1)
        {
            printf("Podaj kolejne liczby: ");

            while (1)
            {
                if (!scanf("%d", &temp))
                {
                    printf("Incorrect input");
                    array_destroy_struct(&arr);
                    return 1;
                }

                if (temp == 0)
                    break;

                if (array_push_back(arr, temp) == 2)
                {
                    printf("Failed to allocate memory\n");
                    while (getchar() != '\n')
                        ;
                    break;
                }
            }

            if (arr->size == 0)
                printf("Buffer is empty\n");
            else
            {
                array_display(arr);
                printf("\n");
            }
        }

        else if (choice == 2)
        {
            printf("Podaj kolejne liczby: ");

            while (1)
            {
                if (!scanf("%d", &temp))
                {
                    printf("Incorrect input");
                    array_destroy_struct(&arr);
                    return 1;
                }

                if (temp == 0)
                    break;

                array_remove_item(arr, temp);
            }

            if (arr->size == 0)
                printf("Buffer is empty\n");
            else
            {
                array_display(arr);
                printf("\n");
            }
        }

        else
            printf("Incorrect input data\n");
    }

    array_destroy_struct(&arr);

    return 0;
}