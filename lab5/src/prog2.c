#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <lab5.h>

int main(){

    int countLib = 2;
    char* namesLib[] = {"./libFirst.so", "./libSecond.so"};

    int numberOfLyb = 0;
    void* hdl;
    hdl = dlopen(namesLib[numberOfLyb], RTLD_LAZY);
    
    if (hdl == NULL){
        printf("dlopen error\n");
        return -1;
    }

    TypeOfE eType;
    TypeOfStort sortType;

    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wpedantic"
        eType = (TypeOfE)dlsym(hdl, "E"); 
        sortType = (TypeOfStort)dlsym(hdl, "Sort");
    #pragma GCC diagnostic pop

    int choice;
    printf("0: Switch lib;\n");
    printf("1: calculate e;\n");
    printf("2: Bubble sort of array.\n");

    while(scanf("%d", &choice) != EOF){  

        switch (choice) {
            case 0:{

                numberOfLyb = (numberOfLyb + 1) % countLib;

                if (dlclose(hdl) != 0){
                    perror("dlclose error");
                    return -1;
                }

                if ((hdl = dlopen(namesLib[numberOfLyb], RTLD_LAZY)) == NULL){
                    printf("dlopen error\n");
                    return -1;
                }

                #pragma GCC diagnostic push
                #pragma GCC diagnostic ignored "-Wpedantic"
                    eType = (TypeOfE)dlsym(hdl, "E"); 
                    sortType = (TypeOfStort)dlsym(hdl, "Sort");
                #pragma GCC diagnostic pop

                printf("Lib swithced. Used lib %d.\n", numberOfLyb+1);
                break;

            }
            case 1:{

                printf("Enter x to calculate e = ");

                int x;
                scanf("%d", &x);

                float e = (*eType)(x);
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
                    scanf("%d", &arr[i]);
                }

                (*sortType)(arr, size);

                printf("Sorted array: \n");
                for (unsigned long i = 0; i < size; ++i){
                    printf("%d ", arr[i]);
                }

                printf("\n");
                free(arr);
                break;

            }
            default:{

                printf("0: Switch lib;\n");
                printf("1: calculate e;\n");
                printf("2: Bubble sort of array.\n");
                break;

            }
        }

    }
    return 0;

}