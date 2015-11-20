/*
 doubly linked list header
 
 struct Node:   points to node before and the next node also records the command and command length
 InsertAtHead:  insert new node at head of list
 deleteLast:    delete last node if list is full
 deleteChar     delete x amount of letters from output
 Print:         not used, but prints full list in reverse order aka starting from tail
 commandHis:    deals with occurence of up/down arrow
 copyNode:      copy Node argument into line[]
 getLINE:       find '/n' 
 cbreakMode:    eter cbreakMode find line, insert into node at head, reset mode
*/
#ifndef DLL
#define DLL
struct Node  {
	char command[1024];
        int length;
	struct Node* next;
	struct Node* prev;
};

struct Node* GetNewNode(char *line);

void InsertAtHead(char *line);

void deleteLast();

void deleteChar(int num);

void Print();

int commandHis(int x, int i, char *line);

void copyNode(char *line);

void getLINE(char *line);

void cbreakMode(char *line, int numNodes);

#endif