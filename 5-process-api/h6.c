#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    int pid = (int) getpid();
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        int stat;
        int wc = waitpid(pid, &stat, 0);
        printf("hello, I am child (pid:%d) (parent:%d)\n", (int) getpid(), errno);
        if (errno == EINVAL) {
            printf("EINVAL\n");
        } else if (errno == EINTR) {
            printf("EINTR\n");
        } else if (errno == ECHILD) {
            printf("ECHILD\n");
        } else if (errno == EFAULT) {
            printf("EFAULT\n");
        }
    } else {
        sleep(1);
        // parent goes down this path (original process)
        printf("hello, I am parent of %d (pid:%d)\n", rc, (int) getpid());
    }
    return 0;
}
