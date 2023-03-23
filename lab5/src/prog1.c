#include<stdio.h>
#include"lab5.h"
#include<stdlib.h>

int main(){

    int choice;
    printf("1: calculate e;\n");
    printf("2: Bubble sort of array.\n");

    printf("Make a choice: ");

    while(scanf("%d", &choice) != EOF){  
        switch (choice) {
            case 1:{

                printf("Enter x to calculate e = ");

                int x;
                scanf("%d", &x);

                float e = E(x);

                printf("e = %f\n", e);
                break;

            }
            case 2:{

                printf("Size of array = ");

                unsigned long size;
                scanf("%lu", &size);

                int* arr = malloc(size * sizeof(int));

                printf("Filling the array:\n");

                for (unsigned long i = 0; i < size; ++i){
                    scanf("%d", arr + i);
                }

                Sort(arr, size);

                printf("Sorted array: \n");
                for (unsigned long i = 0; i < size; ++i){
                    printf("%d ", arr[i]);
                }

                printf("\n");
                free(arr);
                break;

            }
            default:{

                printf("1: calculate e;\n");
                printf("2: Bubble sort of array.\n");
                break;

            }

        }
        
    }
    return 0;
}