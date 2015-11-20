#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ttymode.h"

int main() {
    
    atexit(tty_atexit);
    tty_cbreak(STDIN_FILENO);
    
    char c;
    //while (c != '\n') {
        
    //}
    while (c != '\n') {
        c = getchar();
        if(c == 27){
            getchar();
            c = getchar();
            if(c == 65){
                putchar('\b');                
                putchar('\b');
                putchar(' ');
                putchar('\b');
                putchar('\b');
                putchar(' ');
                putchar('\b');
                putchar('\b');
                putchar(' ');
                putchar('\b');
                putchar('\b');
                putchar(' ');
                putchar('\b');
                putchar('\b');
                putchar(' ');
                putchar('\b');
                printf("up");

            }
            else if(c == 66){
                printf("\rdown");
            }
        }
            else {        
                printf("%d ", c);
            }
    }
    
    return 0;
}