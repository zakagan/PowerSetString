#include "SinglyLinkedList.h"

/* creates a node for a singularly linked list and appends itself to the top of the stack */
void push(Node **head_node, const char* cstring, const int cstring_length, const int last_index) {
	Node* temp_node = malloc(sizeof(Node));
	assert(temp_node != 0);

	temp_node->S = calloc(sizeof(char), cstring_length); 
	assert(temp_node->S != 0); 
	strncpy(temp_node->S,cstring,cstring_length);

	temp_node->length = cstring_length;
	temp_node->last_index = last_index;
	temp_node->next = *head_node;               // Next is really the previously pushed node
	*head_node =temp_node;
} 

/* removes the top of the stack and returns it */
Node* pop(Node **head_node) {
		Node *temp_node = *head_node; // grab the current head
		*head_node = temp_node->next; // remove head from stack	
		return temp_node;	
}

// Frees memory usd back the singularly linked list
void destroyStack(Node *stack) {
	Node *item;
	while(stack!=NULL) {
		item=pop(&stack);
		free(item->S);
		free(item);		
	}
}