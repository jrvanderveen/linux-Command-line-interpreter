#include <stdio.h>
#include "result.h"

#define MIN_FLAG -2147483648

/*
 input: both numbers found, oporator, and error value
 output: result of oporation
 if no error was found then determine what the oporator is and return firstN (oporator) seccondN
 */

int returnResult(int firstN, int seccondN, char oporator, short error, short pass){
    if(error == 0 && pass == 3) {
            if(oporator == '+'){
                printf("%d %c %d ",firstN,oporator,seccondN);
                return (firstN + seccondN);
            }
            else if(oporator == '-'){
                printf("%d %c %d ",firstN,oporator,seccondN);
                return (firstN - seccondN);
            }
            else if(oporator == '*'){
                printf("%d %c %d ",firstN,oporator,seccondN);
                return (firstN * seccondN);
            }
            else{
                if(seccondN == 0){
                    printf("Cant divide by zero.\n");
                    return MIN_FLAG;
                }
                printf("%d %c %d ",firstN,oporator,seccondN);
                return (firstN / seccondN);
            }
        }
return MIN_FLAG;
}
