#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("hello world (pid:%d)\n", (int) getpid());
    int test = 100;
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello, I am child (test:%d)\n", test);
    } else {
        test = 200;
        // parent goes down this path (original process)
        printf("hello, I am parent of %d (test:%d)\n", rc, test);
    }
    return 0;
}
