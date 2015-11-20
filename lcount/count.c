/*
 helper functions for lcount.c
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "count.h"
/*
 addChar - add character found to count of all letters found
 */
void addChar (char c, int *char_count){
    if(c>='a' && c<='z'){
        ++char_count[c-'a'];
    }
    if(c>='A' && c<='Z'){
        ++char_count[c-'A'];
    }
}

/*
 printResult - print the results of counting all characters
 */
void printRsult (int *char_count){
    int ch;
    for(ch = 'a'; ch<='z';++ch){
        printf("%c:%d ", ch, char_count[ch-'a']);
    }
    printf("\n");
}

/*
 argFiles - if argument files are given handle them in this function
    check if file exists and is readable 
    print results only if valid file found otherwise print an error message
 */

void argFiles(int *char_count, int c, int x, int argc, char *argv[]){
    unsigned valid_arg = 0;    
    for(x = 1; x<(argc); x++){
        if(access(argv[x], F_OK) != -1){
            if(access(argv[x], R_OK) != -1){
                valid_arg = 1;
                FILE *file = fopen(argv[x],"r");
                while((c=fgetc(file))!=EOF){
                    addChar(c, char_count);
                }
                
            }
            else{
                printf("Input %d %s: Permisions faluire \n", x, argv[x]);
            }
        }
        else{
            printf("Input %d %s: File not Found \n",x, argv[x]);
        }
    }
    if(valid_arg != 0){
        printRsult (char_count);
    }
}