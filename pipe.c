#include <sys/wait.h>
#include <stdlib.h> 
#include <string.h> 
#include <stdio.h>   
#include <unistd.h>
#include <sys/types.h>
#include <err.h>
#include <stdarg.h>
#include <errno.h>

//#include "pipe.h"
#include "getTokens/tokenizer.h"  //arguments handled here

int main(int argc, char** argv)
{
    int fd[2];
    pid_t pid;
    pid_t pid2;
    int childSt;
    int hell;
    struct arguments args;
    char line[1024];

    while (fgets(line, 1024, stdin)) {
        line[strlen(line)-1] = '\0';
        //////////////////////////////////////////////////////////////          /
        args = finArgs(line);
        pipe(fd);
        pid = fork();
        if (pid > 0)       // PARENT 
        {
            close(fd[1]);	//close write end 
            if (fd[0] != STDIN_FILENO) 
            {
                if ((dup2(fd[0], STDIN_FILENO)) != STDIN_FILENO)
                {
                    printf("dup2 error to stdin\n");
                    close(fd[0]);	
                }
            }
            pid2 = fork();
            if(pid2 == 0){
                if (execvp(args.pipeArgs[0], args.pipeArgs) < 0)
                    printf("parent error \n");       
            }
            else {
                wait(&childSt);
                freopen("/dev/tty","r",stdin);
                freopen("/dev/tty", "w+", stdout);
            }
        }
        
        else    // CHILD
        {
            close(fd[0]);
            if (fd[1] != STDOUT_FILENO)
            {
                if ((dup2(fd[1], STDOUT_FILENO)) != STDOUT_FILENO)
                {
                    printf("dup2 error to stdout\n");
                    close(fd[1]);
                }
            }
            if (execvp(args.args[0], args.args) < 0)
                printf("child error \n");	
        }
    }
    return(0);
}
   
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	/* forking 
		// call to fork and check for error 
	if ( (pid = fork()) < 0)
		printf("fork error");
	
	// child 
	else if (pid == 0) 
	{		
		execvp(argv[1], argv); 
		printf("couldn't execute: %s\n", argv[1]);
		exit(127);
	}
	
	//parent 
	if ( (pid = waitpid(pid, &status, 0)) < 0)
		printf("waitpid error");  */


