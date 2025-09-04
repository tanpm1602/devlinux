#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void stack_overflow() {
    int var[1000];
    var[9] = 1;
    stack_overflow();
}

void memory_leak()
{
    for (int i=0; i<10; i++) 
    {
        int *ptr = (int*)malloc(sizeof(int)*1000);
    } 
}

void out_of_memory() {
    while (1) {
        int *ptr = (int*)malloc(sizeof(int)*1000);

        if (ptr == NULL) {
            printf("Out of memory!\n");
            break;
        }
    }
}

int main() 
{
    char command[50];
    if (fgets(command, sizeof(command), stdin))
    {
        printf("Your command: ");
        if (strcmp(command, "./memory_lab stack_overflow\n") == 0)
        {
            printf("%s", "stack_overflow\n");
            stack_overflow();
        }
        else if (strcmp(command, "./memory_lab memory_leak\n") == 0) 
        {
            printf("%s", "memory_leak\n");
            memory_leak();
        }
        else if (strcmp(command, "./memory_lab out_of_memory\n") == 0) 
        {
            printf("%s", "out_of_memory\n");
            out_of_memory();
        }
    }
}

