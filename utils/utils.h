/*
 util.h utility functions for cli main()
 
 *vpl:          makes sure cd command is limited
 cd:            change directorys to input
 *pwd:          return pointer to current directory
 incd:          cd command found
 inpwd:         pwd command found
 redirectOut:   if > is found redirect output
 redirectIn:    if < is found redirect in
 myFun:         either clac or lcound command found
 linuxCmd:      not myFun found
 handlePipe:    pipe has been found in command line
 setArrays:     reset memory of all arrays used
 */
#ifndef UTILS
#define UTILS

char *vpl(char *path, int maxLen);

int cd(char *dir);

char *pwd();

void incd(struct arguments args, char *workdir, char *wdPath);

void inpwd (char *workdir);

void redirectOut(struct arguments args, char *outPath);

void redirectIn(struct arguments args, char *inPath);

void myFun(struct arguments args, char *cmdPath, int childSt, int childPd, int pipeT);

void linuxCmd(int childPd, char *binPath, struct arguments args, int childSt, int pipeT);

void handlePipe (int *fd, pid_t childPd, pid_t childPd2, int pipeT, struct arguments args, char *outPath, char *inPath, char *cmdPath, int childSt, char *binPath);

void setArrays(char *cmdPath, char *path, char *inPath, char *outPath, char *binPath, char *wdPath, char *workdir, struct arguments args, int i, char * line);

#endif