#include "HashMap.h"

// Hash function used to store nodes based on their strings
size_t djb2Hash(char* str) {
	size_t hash = 5381;
	int c;
	while ((c=*str++)) {
		hash = ((hash << 5) + hash) ^ c;
	}
	return hash;
}

// Creates memory space for a hash map of character & their frequency values within the base string
HashMap* hashMapCreate(size_t size)
{
    HashMap* m;

    m = malloc(sizeof(HashMap));
    assert(m != 0);

    m->size = size;
    m->map = calloc(m->size, sizeof(Node*));
    assert(m->map != 0);

    return m;
}

// Frees memory used for a hash map
void hashMapDestroy(HashMap* m)
{
    int i;
    for(i=0; i < m->size; i++) {
    	if(m->map[i]) {
    		destroyStack(m->map[i]);
    	}
    }
    free(m->map);
    free(m);
}

// inserts a new entry into the hash map structure
void hashMapInsert(HashMap* m, Node* n)
{
    size_t h;
    Node* chained_entry;
    h = djb2Hash(n->S) % m->size;
    chained_entry = m->map[h];      //this hash table uses chaining to resolve collisons
    if (chained_entry==0) {
		push(&m->map[h], n->S, n->length, 0);
	} else {
		while(chained_entry != 0) {
			if(strncmp(chained_entry->S,n->S,n->length) == 0) {
				printf("\t%s\n", " Duplicate detected!");
				return;   // Duplicate are not added again to the chain
			}
			chained_entry = chained_entry->next;
		}
		printf("\t%s\n", " Collison detected!");
		push(&m->map[h], n->S, n->length,0);
	} 
}
