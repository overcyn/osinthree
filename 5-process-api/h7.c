#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        close(STDOUT_FILENO);
        // child (new process)
        printf("hello, I am child\n");
    } else {
        wait(NULL);
        // parent goes down this path (original process)
        printf("hello, I am parent of %d\n", rc);
    }
    return 0;
}
