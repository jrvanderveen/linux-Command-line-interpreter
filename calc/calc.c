/*
 input is integer oporator integer 
 print result of calculation
 */
#include <stdio.h>
#include <string.h>
#include "result.h"

#define MAX_L 256
#define MIN_FLAG -2147483648

int main (int argc, char** argv) {

    char line[MAX_L];
    long result = MIN_FLAG;
    int i;
    // get a line from stdin evaluate equation
    while (fgets(line, MAX_L, stdin)) {
        // remove the '\n' from the end of the line
        line[strlen(line)-1] = '\0';
        // get and display the tokens in line
        result = getresult(line);
        if(result!=MIN_FLAG){printf(" = %lu \n",result);}
    }
    return 0;
}
