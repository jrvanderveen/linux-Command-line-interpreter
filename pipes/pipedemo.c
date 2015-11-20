#include <sys/wait.h>
#include <stdlib.h> 
#include <string.h> 
#include <stdio.h>   
#include <unistd.h>
#include <sys/types.h>
#include <err.h>
#include <stdarg.h>

int
main(int argc, char *argv[])
{
	int fd[2];
	pid_t pid;
        int childSt;
	
	char *arg[2];
	char *srg[3];
	arg[0] = (char *)calloc(1, sizeof(char));
	arg[0][0] = '\0';
	arg[1] = (char *)0;
	
        srg[0] = (char *)calloc(4, sizeof(char));
	strcpy(srg[0], "cat");
	srg[1] = (char *)calloc(13, sizeof(char));
	strcpy(srg[1], "pipedemo.c");
	srg[2] = (char *)0;
	
	printf(" '%s %s | %s' \n", srg[0], srg[1], arg[0]);

	
	pipe(fd);
	pid = fork();
	if(arg[0][0] != '\0'){
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
                    if (execvp(arg[0], arg) < 0)
                            printf("parent error \n"); 
                    if (wait(NULL) < 0)
                            printf("couldn't wait\n");
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
                    if (execvp(srg[0], srg) < 0)
                            printf("child error \n");	
            }        
            
        }

        else if(arg[0][0] == '\0'){
                if(pid == 0){
                    if(execvp(srg[0],srg) == -1){exit(0);}
                }
                else {
                    wait(&childSt);
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
	
	// parent 
	if ( (pid = waitpid(pid, &status, 0)) < 0)
		printf("waitpid error");  */


