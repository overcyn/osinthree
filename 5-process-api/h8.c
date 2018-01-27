#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>


int main(int argc, char *argv[])
{
    int fd[2];
    if (pipe(fd) == -1) {
        return -1;
    }
    
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        write(STDOUT_FILENO, "hello, I am child.", 18);
        write(STDOUT_FILENO, "hello, I am child.", 18);
        printf("hello, I am child.");
    } else {
        wait(NULL);
        
        int err = dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        char buffer[100];
        int count = read(STDIN_FILENO, buffer, 100);
        buffer[count] = '\0';
        // parent goes down this path (original process)
        printf("hello, I am parent of (%s) %d\n", buffer, count);
    }
    return 0;
}