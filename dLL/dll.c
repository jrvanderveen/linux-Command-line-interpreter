//Doubly Linked List implementation for command history 
/*structure of list
  struct Node  {
	char command[1024];
        int length;
	struct Node* next;
	struct Node* prev;
}*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>

#include "dll.h"
#include "../inputMode/ttymode.h"

struct Node* head; //global pointing to head
struct Node* tail; //global pointing to tail
struct Node* current;//global pointing to current node

//Creates a new Node and returns pointer to it. 
struct Node* GetNewNode(char *line) {
	struct Node* newCommand = (struct Node*)malloc(sizeof(struct Node));
        int i = 0;
        while(line[i] != '\0'){
            newCommand->command[i] = line[i];
            i++;
        }
        newCommand->length = i;
        newCommand->command[i] = '\0';
        newCommand->prev = NULL;
	newCommand->next = NULL;
        return newCommand;
}

//Inserts a Node at head of doubly linked list
void InsertAtHead(char *line) {
	struct Node* newCommand = GetNewNode(line);
	if(head == NULL) {
		head = newCommand;
                tail = newCommand;
		return;
	}
	head->prev = newCommand;
	newCommand->next = head; 
	head = newCommand;
}
//Use tail to delete the last node
void deleteLast(){
    struct Node* temp = tail;
    tail = temp->prev;
    free(tail->next);
    tail->next = NULL;
}
//Delete num chars from line
void deleteChar(int num){
    int i = 0;
    for(i; i < num; i++){
        putchar('\b');
        putchar(' ');
        putchar('\b');    
    }
}
//Print in reverse order
/*void Print() {
	struct Node* temp = tail;
	while(temp != NULL) {
		printf("%s \n",temp->command);
                deleteChar(temp->length);
		temp = temp->prev;
	}
	free(temp);
}*/
//Deals with occurance of up/down input
int commandHis(int x, int i, char *line){
    deleteChar(i);
    if(current != NULL){
        if(x == 1){           
            if(current->next == NULL){
                printf("%s", current->command);
                return current->length;
            }
            current = current->next;
            printf("%s", current->command);
            return current->length;
        }
        else{
            if(current->prev == NULL){
                current = NULL;
                return -1;
            }       
            current = current->prev;
            printf("%s", current->command);
            return current->length;
            
        }
    }
    return 0;
}
//cope command from node into line
void copyNode(char *line){
    int i = 0;
    if(current != NULL){
        while(current->command[i] != '\0'){
            line[i] = current->command[i];
            i++;
        }
        
    }
}
//Get the user input char by char
//special cases for Ctr+D, up/down arrow, backspace
void getLINE(char *line){
    char c = 'a';
    int i = 0;
    int base = 0;
    while (c != '\n' && i < 1024) {
        c = getchar();
        if(c == 4){
            exit(1);
        } 
        if(c == 27){
            base = 0;
            while(c == 27){
                getchar();
                c = getchar();
                if(c == 65){
                    if(head != NULL){
                        if(base == 0){
                            base = 1;
                            deleteChar(i);
                            i = head->length;
                            printf("%s", head->command);
                            current = head;
                        }
                        else{
                            i = commandHis(1, i, line);
                        }
                    }
                }
                else if(c == 66){
                    i = commandHis(-1, i, line);
                    if(i == -1){
                        i = 0;
                        base = 0;
                    }
                }
                c = getchar();
            }
            copyNode(line);
            current = NULL;
        }
        if (c == 127){
            if(i != 0){
                deleteChar(1);
                line[i-1] = '\0';
                i-=1;                        
                
            }
        }
        if (c > 31 && c < 127){
            line[i] = c;
            i += 1;
            if(c != '\n'){
                printf("%c", c);
            }  
        }
    }
    line[i] = '\0';
}
//Change to cbreak mode 
//Inset new command into list and reset mode
void cbreakMode(char *line, int numNodes) {
        tty_cbreak(STDIN_FILENO);      
        getLINE(line);
        if(line[0] != '\0'){
            if(numNodes == 30){
                deleteLast();
            }
            InsertAtHead(line);
        }

        printf("\n");
        tty_reset(STDIN_FILENO);
}















