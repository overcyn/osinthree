#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int *x = malloc(100*sizeof(int));
    free(x);
    x[100] = 0;
    return 0;
}
