/*
 count.h
 
 initializes functions used in lcount
 addChar:        add character found to count of all letters found
 printResult:    print the results of counting all characters
 argFiles:       if argument files are given handle them in this function
 
 */ 

#ifndef COUNT
#define COUNT

void addChar (char c, int *char_count); 

void printRsult (int *char_count);

void argFiles (int *char_count, int c, int x, int argc, char *argv[]);

#endif