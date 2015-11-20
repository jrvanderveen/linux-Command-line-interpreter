/*
 helper functions for cli.c
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "../getTokens/tokenizer.h"
#include "utils.h"

#define MAX_PATH 512
#define MAX_L 1024
//Validate length of path
////////////////////////////////////////////
char *vpl(char *path, int maxLen){
    int len;
    len = strlen(path);
    if(len > 0){
        return path;
    }
    else{
        return "\0";
    }
}
// Change dir for cli prog
int cd (char *dir) {
    if(chdir(dir) ==0){
        return 0;
    }
    else{
     printf("No such directory:%s \n", dir);
    }
    return 1;
}


//Return the current working directory

char *pwd () {
   char cwd[MAX_PATH];
   if (getcwd(cwd, sizeof(cwd)) != NULL){
       strcat(cwd, "/");
    }
   else
       perror("error");
   return cwd;
}
//pupulate redirectIn
void redirectIn (struct arguments args, char *inPath){
    if(args.dIN[0] != '\0'){
        if(access(args.dIN, F_OK) != -1){
            if(access(args.dIN, R_OK) != -1){
                strcpy(inPath, pwd());
                strcpy(inPath, args.dIN);
                freopen(inPath,"r",stdin);
            }
        }
    }
}
//populate redirectOut
void redirectOut (struct arguments args, char *outPath){
    if(args.dOUT[0] != '\0'){
        strcpy(outPath, pwd());
        strcpy(outPath, args.dOUT);
        freopen(outPath, "w", stdout);
    }
}
//pwd has been found with no pipes
void inpwd (char *workdir){
    strcpy(workdir, pwd());
    workdir[strlen(workdir)-1] = '\0';
    printf("%s",workdir);
    workdir[strlen(workdir)] = '/';    
}
//cd command found
// '/' in line[0] means absolute path
void incd(struct arguments args, char *workdir, char *wdPath){
    if(args.args[1][0] == '/'){
        if(cd(args.args[1]) == 0){
            memset(workdir, '\0', sizeof(char));
            strcpy(workdir, pwd());
            workdir[strlen(workdir)-1] = '\0';
            printf("cwd changed to %s\n",workdir);
            workdir[strlen(workdir)] = '/';                        
        }
    }
    else if(cd(strcat(wdPath, vpl(args.args[1], MAX_PATH))) == 0){
        memset(workdir, '\0', sizeof(char));
        strcpy(workdir, pwd());
        workdir[strlen(workdir)-1] = '\0';
        printf("cwd changed to %s\n",workdir);
        workdir[strlen(workdir)] = '/';
        
    }    
}
//calc or lcount found execute command with pwd<-arg as path
void myFun(struct arguments args, char *cmdPath, int childSt, int childPd, int pipeT){
    if(childPd == 0){
         if(pipeT == 0){
            strcat(cmdPath, args.pipeArgs[0]);
            strcat(cmdPath, "/");
            strcat(cmdPath, args.pipeArgs[0]);
            if(execvp(cmdPath,args.pipeArgs) == -1){exit(0);}
         }
         else{
            strcat(cmdPath, args.args[0]);
            strcat(cmdPath, "/");
            strcat(cmdPath, args.args[0]);
            if(execvp(cmdPath,args.args) == -1){exit(0);}
        }
    }
    else {
        wait(&childSt);
        freopen("/dev/tty","r",stdin);
        freopen("/dev/tty", "w+", stdout);
    }    
}
//not myFun found ececute command
 void linuxCmd(int childPd, char *binPath, struct arguments args, int childSt, int pipeT){
     if(childPd == 0){
         if(pipeT == 0){
            strcat(binPath, args.pipeArgs[0]);
            if(execvp(binPath,args.pipeArgs) == -1){exit(0);}
         }
         else{
             strcat(binPath, args.args[0]);
             if(execvp(binPath,args.args) == -1){exit(0);}
        }
     }
     else {
         wait(&childSt);
         freopen("/dev/tty","r",stdin);
         freopen("/dev/tty", "w+", stdout);
     }     
}
//if a pipe has been found
//fork the process and close correct filedescriptors
//if child execute the first command.  this will pipe output into next command executed
//if parrent fork again and wait, let child ececute seccond command
void handlePipe (int *fd, pid_t childPd, pid_t childPd2, int pipeT, struct arguments args, char *outPath, char *inPath, char *cmdPath, int childSt, char *binPath){
    pipe(fd);
    childPd = fork();
    if (childPd > 0)       // PARENT 
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
        pipeT = 0;
        redirectOut(args, outPath);
        childPd2 = fork();
        if (!strcmp(args.pipeArgs[0],"calc") || !strcmp(args.pipeArgs[0],"lcount")){
            myFun(args, cmdPath, childSt, childPd2, pipeT);
        }
        else {
            linuxCmd(childPd2, binPath, args, childSt, pipeT);
        }
        if (wait(NULL) < 0)
            printf("couldn't wait\n");
    }
    else    // CHILD
    {
        close(fd[0]);
        if (fd[1] != STDOUT_FILENO)
        {
            if ((dup2(fd[1], STDOUT_FILENO)) != STDOUT_FILENO)
            {                    pipe(fd);
                printf("dup2 error to stdout\n");
                close(fd[1]);
            }
        }
        pipeT = 1;
        redirectIn(args, inPath);
        if (!strcmp(args.args[0],"calc") || !strcmp(args.args[0],"lcount")){
            myFun(args, cmdPath, childSt, childPd, pipeT);
        }
        else {
            linuxCmd(childPd, binPath, args, childSt, pipeT);
        }
    }     
}
//reset mem for everything that needss it
void setArrays(char *cmdPath, char *path, char *inPath, char *outPath, char *binPath, char *wdPath, char *workdir, struct arguments args, int i, char *line){
    memset(line, '\0', sizeof(char));
    
    memset(cmdPath, '\0', sizeof(char));
    strcat(cmdPath, path);

    memset(inPath, '\0', sizeof(char));
    
    memset(outPath, '\0', sizeof(char));
    
    memset(binPath, '\0', sizeof(char));
    
    memset(wdPath, '\0', sizeof(char));
    strcat(wdPath,workdir);
    printf("%%> ");
    
    for(i = 0; i < args.numTokens; i++){
        free(args.args[i]);
    }    
    for(i = 0; i < args.numPipeArgs; i++){
        free(args.pipeArgs[i]);
    } 
}