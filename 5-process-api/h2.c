#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("hello world (pid:%d)\n", (int) getpid());
    int fd = open("./h2.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
    int test = 100;
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello, I am child (test:%d)\n", test);
        write(fd, "child\n", 6);
    } else {
        test = 200;
        // parent goes down this path (original process)
        wait(NULL);
        
        printf("hello, I am parent of %d (test:%d)\n", rc, test);
        write(fd, "parent\n", 7);
    }
    return 0;
}
