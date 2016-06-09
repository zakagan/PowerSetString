//
// HashMap.h
//

#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "SinglyLinkedList.h"

//A list of Nodes, indexed by hash values
typedef struct {
    int size;            // size of the pointer list
    Node **map;
} HashMap;

size_t djb2Hash(char* str);

HashMap* hashMapCreate(size_t size);

void hashMapDestroy(HashMap* m);

int hashMapInsert(HashMap* m, Node* n);


#endif