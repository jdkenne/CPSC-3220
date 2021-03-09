#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char *ptr;
    int val, result;
    val = strtol(argv[1], &ptr, 10);
    result = val / 2;
    printf("Result is: %d\n\n",result);

    return 0;
}


