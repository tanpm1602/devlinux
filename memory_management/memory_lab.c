#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void stack_overflow()
{
    printf("stack_overflow function is running\n");
    int var[1000];
    var[9] = 1;
    stack_overflow();
}

void memory_leak()
{
    printf("memory_leak function is running\n");
    int *ptr = (int *)malloc(sizeof(int) * 1000);
}

void out_of_memory()
{
    printf("out_of_memory is running\n");

    while (1)
    {
        int *ptr = (int *)malloc(sizeof(int) * 1000);
        if (ptr == NULL)
        {
            printf("Out of memory!\n");
            break;
        }
    }
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Choose one of the functions you want to run: stack_overflow, out_of_memory, memory_leak\n");
        return 1;
    }

    const char *cmd = argv[1];
    if (strcmp(cmd, "stack_overflow") == 0) {
        printf("Running: stack_overflow\n");
        stack_overflow(); 
    }
    else if (strcmp(cmd, "memory_leak") == 0) {
        printf("Running: memory_leak\n");
        memory_leak();
    }
    else if (strcmp(cmd, "out_of_memory") == 0) {
        printf("Running: out_of_memory\n");
        out_of_memory();
    }
    else {
        fprintf(stderr, "Unknown command: %s\n\n", cmd);
        return 2;
    }

    return 0;
}
