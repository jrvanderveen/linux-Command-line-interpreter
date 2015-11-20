/*
 main program for comandline interpreter
 this programs reads from stdin one char at a time until a line is found
 once a line is found it is returned in a stuct form
    
    struct arguments{
        char **args;
        char dIN[100];
        char dOUT[100];
        int numTokens;
        char **pipeArgs
    }
 from there the input is analyzed for pipes and redirection and precedes acordingly
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#include "inputMode/ttymode.h"
#include "dLL/dll.h"
#include "getTokens/tokenizer.h"
#include "utils/utils.h"

#define MAX_L 1024
#define MAX_PATH 512

struct Node* head; //global pointing to head
struct Node* tail; //global pointing to tail
struct Node* current;//global pointing to current node



int main (int argc, char** argv) {
    //cbreakMode requirements
    atexit(tty_atexit);
    
    head = NULL; 
    tail = NULL;
    current = NULL;
    
    int numNodes = 0;
    //main progs variables    
    struct arguments args;
    pid_t childPd = -1;
    pid_t childPd2 = -1;
    int i = 0;
    int childSt = 0;
    char workdir[MAX_L];
    char line[MAX_L];
    char cmdPath[MAX_L]; strcpy(cmdPath, pwd());
    char wdPath[MAX_L];strcpy(wdPath, pwd());
    char path[MAX_L];strcpy(path, pwd());
    char binPath[MAX_L];
    char inPath[MAX_L];
    char outPath[MAX_L];
    int fd[2];
    int pipeT = 0;
    //make sure all paths are set correctly
    setArrays(cmdPath, path, inPath, outPath, binPath, wdPath, workdir, args, i, line);
    while (1) {
        //handels all user input aka line and Ctr+D, Ctr+C still terminates cli
        cbreakMode(line, numNodes);
        //if input has been found procede with arguments
        if(line[0] != '\0'){
            if(numNodes != 30){
                numNodes += 1;
            }
            args = finArgs(line);
            if(args.numTokens > 0){
            /*
            pwd and cd are build in functions and do not execute
            pwd returns current working directory
            cd changes directiory if a valid input is entered
            
            if user types exit end program
            */            
                if(!strcmp(args.args[0],"pwd") && args.numPipeArgs == 0){
                    inpwd(workdir);
                }
                else if(!strcmp(args.args[0],"cd") && args.args[1] != NULL){
                    incd(args, workdir, wdPath);
                }
                else if(!strcmp(args.args[0],"exit")){
                    exit(0);
                }
            /*
            calc and lcount are my functions 
            if they are given as an argument then execute them
            path = pwd() when program is lannched
            */
                else if ((!strcmp(args.args[0],"calc") || !strcmp(args.args[0],"lcount")) && args.numPipeArgs == 0){
                    childPd = fork();
                    redirectOut(args, outPath);
                    redirectIn(args, inPath);
                    pipeT = 1;
                    myFun(args, cmdPath, childSt, childPd, pipeT);
                }
            /*
            if other checks failed then test aginst built in linux functions
            */
                else if(args.numPipeArgs == 0) {
                    redirectIn(args, inPath);
                    redirectOut(args, outPath);
                    childPd = fork();
                    pipeT = 1;
                    linuxCmd(childPd, binPath, args, childSt, pipeT);
                }
            //if a pipe has been found
                else if(args.numPipeArgs != 0){
                    handlePipe (fd, childPd, childPd2, pipeT, args, outPath, inPath, cmdPath, childSt, binPath);
                }
                
            }
            //something went wrong with the user input with pipes or redirection
            else {
                
                printf("Usage error: Pip/Redirection/NULL argumnet %d \n %%>", args.numTokens);
            }
            
            //memory of paths and arguments needs to be eith freed or reset
            setArrays(cmdPath, path, inPath, outPath, binPath, wdPath, workdir, args, i, line);
        }
        //no input found
        else{
            printf("%%> ");
        }
    }
    return 0;
}



















