/*
args structure:
struct arguments{
    char **args;
    char dIN[100];
    char dOUT[100];
    int numTokens;
    char **pipeArgs;
    int numPipeArgs;
}
 */


/* tokenizer.h

    header file for tokenizer
    breaks a string into substrings separated by spaces
    substrings enclosed in double quotes may contain space
*/

// gettokens returns an array of strings
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"

#define MAX_LEN		256

struct arguments finArgs (char *line){
    struct arguments tokens;
    strcpy(tokens.dOUT, "\0");
    strcpy(tokens.dIN, "\0");
    int i = 0, j = 0, z = 0;
    int num_tokens = 0, token_len = 0;
    int letter_flag = 0, direction_flag = 0, pipeFlag = 0;
    int start_token[MAX_LEN];
    int end_token[MAX_LEN];
    char c;
    char file[100];

/*
counts the number of tokens in the line and records start and end positions
*/
    while(line[i] != '\0'){
        c = line[i];
        if(c == '<' || c == '>'){
            if(c == '<' && tokens.dIN[0] == '\0'){
                if(pipeFlag == 0){
                    direction_flag = 1;
                }
                else{
                    tokens.numTokens = -1;
                    return tokens;                    
                }
            }
            else if(c == '>' && tokens.dOUT[0] == '\0'){
                direction_flag = 2;
            }
            else{
                tokens.numTokens = -1;
                return tokens;
            }
            i++;
            c = line[i];
        }
        if(c == '|'){
            if(tokens.dOUT[0] != '\0' || pipeFlag != 0){
                tokens.numTokens = -1;
                return tokens;
            }
            pipeFlag = num_tokens;
            i++;
            c = line[i];
        }
        if((c >= '#' && c <= '~') || c == '!'){
            if(direction_flag != 0){
                memset(file, '\0', sizeof(file));
                while(((c >= '#' && c <= '~') || c == '!') && z < 99){
                    file[z] = c;
                    i++;
                    z++;
                    c = line[i];
                }
                z = 0;
                if(direction_flag == 1){
                    strcpy(tokens.dIN, file);
                }
                else if(direction_flag == 2){
                    strcpy(tokens.dOUT, file);
                }
                direction_flag = 0;
            }
            else {
                start_token[num_tokens] = i;
                while((c >= '#' && c <= '~') || c == '!'){
                    i++;
                    c = line[i];
                }
                end_token[num_tokens] = i;
                num_tokens++;
            }
        }
        if(line[i] == '"'){
            i++;
            start_token[num_tokens] = i;
            c = line[i];
            while(c != '"' && c != '\0'){
                i++;
                c = line[i];
                if((c >= '#' && c <= '~') || c == '!'){
                    letter_flag = 1;
                }
            }
            if(letter_flag){
                end_token[num_tokens] = i;
                num_tokens++;
                letter_flag = 0;
            }
        }
        if(line[i] != '\0'){i++;}
    }
/*
uses num_tokens to allocate enought pointer space
then uses the start and end positions of each token to allocate enough space for each token and \0
using the start position record the token into its right place and terminate
*/



    if(pipeFlag == 0){
        tokens.args = (char **)malloc((num_tokens + 1) * sizeof(char *));
        for(i = 0; i < num_tokens; i++){
            token_len = end_token[i] - start_token[i] + 1;
            tokens.args[i] = (char *)malloc(token_len * sizeof(char));
            for(j = 0; j < token_len-1; j++){
                tokens.args[i][j] = line[start_token[i]+j];
            }
            tokens.args[i][j+1] = '\0';
        }
        tokens.args[num_tokens] = NULL;
        tokens.numTokens = num_tokens;
    }
    else{
        int q = 0;
        tokens.args = (char **)malloc((pipeFlag + 1) * sizeof(char *));
        tokens.pipeArgs = (char **)malloc(((num_tokens - pipeFlag) + 1) * sizeof(char *));
        for(i = 0; i < num_tokens; i++){
            token_len = end_token[i] - start_token[i] + 1;
            if(i < pipeFlag){
                tokens.args[i] = (char *)malloc(token_len * sizeof(char));
                for(j = 0; j < token_len-1; j++){
                    tokens.args[i][j] = line[start_token[i]+j];
                }
                tokens.args[i][j+1] = '\0';
            }
            else{
                tokens.pipeArgs[q] = (char *)malloc(token_len * sizeof(char));
                for(j = 0; j < token_len-1; j++){
                    tokens.pipeArgs[q][j] = line[start_token[i]+j];
                }
                tokens.pipeArgs[q][j+1] = '\0';
                q++;
            }
        }    
        tokens.args[pipeFlag] = NULL;
        tokens.numTokens = pipeFlag;
        tokens.pipeArgs[num_tokens - pipeFlag] = NULL;
        tokens.numPipeArgs = num_tokens - pipeFlag;
    }
return tokens;
}

















