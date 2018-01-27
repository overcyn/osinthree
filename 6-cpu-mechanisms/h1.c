#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>

int iterations = 1000000;

int main(int argc, char *argv[]) {
    int p1[2];
    int p2[2];
    if (pipe(p1) != 0 || pipe(p2) != 0) {
        return -1;
    }
    
    int pid = fork();
    if (pid < 0) {
        return -1;
    } else if (pid == 0) {
        setbuf(stdout, NULL);
        close(p1[0]);
        
        char buf[1] = {'.'};
        for (int i = 0; i < iterations; i++) {
            if (write(p1[1], buf, 1) != 1) {
                printf("error %d", errno);
                return -1;
            }
            // printf("cw%c, ", buf[0]);
            
            if (read(p2[0], buf, 1) != 1) {
                printf("error4 %d", errno);
                return -1;
            }
            // printf("cr%c, ", buf[0]);
        }
    } else {
        setbuf(stdout, NULL);
        close(p2[0]);
        
        struct timespec ts;
        if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) {
            printf("clock error %d", errno);
        }
        
        char buf[1] = {'-'};
        for (int i = 0; i < iterations; i++) {
            if (write(p2[1], buf, 1) != 1) {
                printf("error2 %d", errno);
                return -1;
            }
            // printf("pw%c, ", buf[0]);
            
            if (read(p1[0], buf, 1) != 1) {
                printf("error3 %d", errno);
                return -1;
            }
            // printf("pr%c, ", buf[0]);
        }
        
        struct timespec ts2;
        if (clock_gettime(CLOCK_MONOTONIC, &ts2) != 0) {
            printf("clock error %d", errno);
        }
        
        long ns = ((ts2.tv_sec - ts.tv_sec)*1e9 + ts2.tv_nsec - ts.tv_nsec)/iterations;
        ns = ns / 2; // divide by 2 because there are twice as many context switches as iterations
        printf("ns:%ld\n", ns);
    }
    return 0;
}
