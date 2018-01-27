#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

int
main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        // char *myargs[2];
        // myargs[0] = strdup("ls");   // program: "wc" (word count)
        // myargs[1] = NULL;           // marks end of array
        // execvp(myargs[0], myargs);  // runs word count
        
        // execlp("ls", "ls", NULL);
        
        char *env[3];
        env[0] = strdup("PWD=/Users/overcyn/Workspace/");
        env[1] = strdup("PATH=/bin");
        env[2] = NULL;
        execle("/bin/ls", "ls", NULL, env);
        printf("this shouldn't print out\n");
    } else {
        // parent goes down this path (original process)
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n",
           rc, wc, (int) getpid());
    }
    return 0;
}
