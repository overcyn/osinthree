#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    int iterations = 5000;
    int pageCount = atoi(argv[1]);
    int jump = sysconf(_SC_PAGESIZE) / sizeof(int);
    int *a = calloc(pageCount * jump, sizeof(int));
    
    // Get start time
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) {
        printf("clock error %d", errno);
    }

    for (int j = 0; j < iterations; j++) {
        for (int i = 0; i < pageCount * jump; i += jump) {
            a[i] += 1;
        }
    }
    
    // Get end time
    struct timespec ts2;
    if (clock_gettime(CLOCK_MONOTONIC, &ts2) != 0) {
        printf("clock error %d", errno);
    }
    
    long ns = ((ts2.tv_sec - ts.tv_sec)*1e9 + ts2.tv_nsec - ts.tv_nsec);
    ns = ns/iterations/pageCount;
    printf("%ld", ns);
    
    return 0;
}