//
// SinglyLinkedList.h
//

#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

// A singularly linked list used for a stack structure
typedef struct node {
	char* S;
	int length, last_index;    //length is the number of elements in the power set
	struct node* next;
} Node;

void push(Node **head_node, const char* cstring, const int cstring_length, const int last_index);

Node* pop(Node **head_node);

void destroyStack(Node *stack);

#endif