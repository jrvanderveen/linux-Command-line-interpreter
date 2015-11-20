#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include "result.h"

//globals
int numLen = 0, numLen2 = 0; //used to correct for zeros on end of number eg: 10 -> 1
int i = 0;                   //counter for line used in multiple functions
char c;                      //c = line[i]

/* 
 getresult(char *line);
 input: array of charecters line[], holds stdin from user or file
 output: returns interger evaluations of input expression or long min-long as error 
 overview: this function is basically a state machine with cases: no nums found, first num found, oporator found, seccond num found
 if cant find one then an error message with print and will wait for next input
 */
int getresult (char *line){
        numLen = 0, numLen2 = 0;i = 0; //reset globals for each itteration
        int firstN = 0, seccondN = 0;
        char oporator;
        short error = 0, neg = 1;
        short pass = 0;
        while(line[i] >= ' '  && error == 0){
                c = line[i];
                //if first interger has not been found either find valid integer or return error
                if(pass == 0){
                    if((c < '0' || c > '9') && c != ' ' && c != '-'|| (c == '-' && neg == -1)){
                        error = 1;
                        printf("calc Usage Error input %d: calc arguments are integer, operator(+-*/), integer\n",(pass+1));
                    }
		    else if(c == '-'){
			neg = -1;
			i++;
	            }
                    else if(c == ' '){
                        i++;;
                    }
                    else{
                        pass = 1;
			firstN = nextNum(line, pass);
                        firstN = reverse(firstN, numLen) * neg;
                    }
                }
                //if first integer has been found either find valid oporator or return error
                else if(pass == 1){
                    if(c != '+' && c != '-' && c != '*' && c != '/' && c != ' '){
                        error = 1;
                        printf("calc Usage Error input %d: calc arguments are integer, operator(+-*/), integer\n",(pass+1));
                    }
                    else if(c == ' '){
                        i++;
                    }
                    else{
                        pass = 2;
                        oporator = c;
                        i++;
                        c = line[i];
		        neg = 1;
                    }
                }
                //if oporator found either find valid integer or return error
                else if(pass == 2){
                   if((c < '0' || c > '9') && c != ' ' && c != '-'|| (c == '-' && neg == -1)){
                        error = 1;
                        printf("calc Usage Error input %d: calc arguments are integer, operator(+-*/), integer\n",(pass+1));
                    }
		    else if(c == '-'){
			neg = -1;
                        i++;
		    }
                    else if(c == ' '){
                        i++;
                    }
                    else{
                        pass = 3;
			seccondN = nextNum(line, pass);
                        seccondN = reverse(seccondN, numLen2);

                    }
                }
                //if seccond num foundcontinue to end of line make sure nothing else there
                else{
                   if(c != ' ' && c != '\0'){
                        error = 1;
                        printf("calc Usage Error3: calc arguments are integer, operator(+-*/), integer\n");
                    }
                    i++;
                }
        }
    return returnResult(firstN,seccondN,oporator,error,pass);
}

/*
 nextNum(char *line, int pass)
 input: array of chars, pass(what part of state machine has passed)
 output: reverse order of any numbers connected in line eg: [..,1,2,3...] = 321
 */
int nextNum (char *line, int pass){
    int nextN = 0;
    int multiplier = 1;
    while(line[i] != '\0' && (c >= '0' && c <= '9')){
        if(pass == 1){numLen++;}
        else{numLen2++;}
        nextN += (multiplier * (c-48));
        multiplier *= 10;
        i++;
        c = line[i];
    }
    return nextN;
}
/*
 reverse(int numRev, int numberLen)
 user input will be read in reverse order
 reverse generates the number the user entered in the correct order
 */
int reverse(int numRev, int numberLen){
    int x = 0;
    int num = 0;
    for(x = 0; x < numberLen; x++){
        if(numRev != 0){
            num = num * 10;
            num = num + numRev%10;
            numRev = numRev/10;
        }
        else{
            num*=10;
        }
    }
    return num;
}
