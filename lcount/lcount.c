/*
 lcount can be executed from cli
 counts all charecters and returns the sum of each
 if args found search files if no then user input
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "count.h"

#define MAX_L 512


int main (int argc, char *argv[]){
    int char_count[26]={0};
    int c,x;

    memset(char_count,0,sizeof(char_count));
    if(argc>1){
        argFiles(char_count, c, x, argc, argv);
    }
    else{
        char line[MAX_L]={'0'};
        memset(char_count,0,sizeof(char_count));
        while (fgets(line, MAX_L, stdin)){
            for(x = 0; x < MAX_L; ++x){
                c = line[x];
                addChar(c, char_count);
            }
            memset(line,'0',sizeof(line));
        }
        printRsult (char_count);
        
    }
    return 0;
}