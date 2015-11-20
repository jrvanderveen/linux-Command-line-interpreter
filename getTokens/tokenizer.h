/* tokenizer.h

	header file for tokenizer
	breaks a string into substrings seperated by spaces
	substrings enclosed in double quotes may contain spaces

*/

// gettokens: returns an array of strings

struct arguments{
    char **args;
    char dIN[100];
    char dOUT[100];
    int numTokens;
    char **pipeArgs;
    int numPipeArgs;
};

struct arguments finArgs (char *line);