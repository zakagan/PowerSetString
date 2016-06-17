#include "PowerSetString.h"

void printPsetAndHashTest(Node *stack, HashMap* m) {
	int found,chain_position, count=0;
	Node *hash_entry, *item=stack;
	printf("\tP(S)={\n");
	while(item != NULL) {
		printf("%d)\t\t{%s} ", count++,item->S);         //Lists the number of the subset within the power set
		found=0;
		chain_position=0;
		size_t h = djb2Hash(item->S) % m->size;
		hash_entry=m->map[h];
		while(hash_entry) {
			chain_position++;
			if(strncmp(hash_entry->S,item->S,item->length)!=0) {
					hash_entry = hash_entry->next;
			} else {
				found=1;
				break;
			}
		}
		if (found) {
			printf("-> hash hit at entry %zu with chain position %d\n",h, chain_position);
		} else if (chain_position) {
			printf("-> hash hit at entry %zu, not located in chain\n",h);
		} else {
			printf("-> hash miss! Hash value %zu is empty! \n", h);
		}
		item=item->next;
	}
	printf("\t};\n");					
}

int calculatePowerSet(char *str, int str_length) {
	int i, collisions=0;
	Node *temp_stack = NULL;
	Node *item=NULL;
	// this stack will be populated and used to replace the need for recursive calls
	printf("%s\n", "Filling stack with single chars from base string");
	for(i=0;i<str_length;i++) { 
		push(&temp_stack, &str[i], 1, i);
		printf("\t %c\n", str[i]);
	}
	printf("%s\n", "Calculating Power Set...");
	push(&saved_stack, "", 0, -1);                   // Adds the empty set
	while(temp_stack!=NULL) {
		item=pop(&temp_stack);
		printf("\t popped %s from the stack \n",item->S);
		push(&saved_stack, item->S, item->length, str_length);    // consider removing saved_map and saved_stack for a more functional design
		collisions += hashMapInsert(saved_map, item);
		printf("\t saved %s\n",saved_stack->S);

		for(i=item->last_index; i<str_length-1; i++){                         //iterates last item through the size of the subset
			push(&temp_stack, item->S, item->length+1, i+1);
			strncat(temp_stack->S,&str[i+1],1);
			printf("\t %s pushed to stack \n",temp_stack->S);
			printf("\t next char: %c\n",str[i+1]);
		}
		destroyNode(item);
	}
	printf("Power Set calculation complete\n");
	return collisions;
}

int main(int argc, char **argv) {
	if (argc<2) {
		printf("A single base string is required as input.\nOptionally you can also enter the buckets for the hash table as a 2nd input.\n");
        return 0;
	}

	int c, i, buckets, collisions, count, proceed=1, buffer_length = 20, str_length = strlen(argv[1]);
	size_t h;
	Node* item;

	if (argc>2) {
		buckets = atoi(argv[2]);
	} else {
		printf("Default load factor is ~50%%\n");
		buckets = (1 << (str_length+1))-1;
	}
	saved_map = hashMapCreate(buckets);

	sortStr(argv[1],str_length);
	collisions = calculatePowerSet(argv[1],str_length);

	printPsetAndHashTest(saved_stack,saved_map);

	printf("Hash table load factor: %d / %d = %f\n", (1<<str_length), buckets, ( (1<<str_length) / (float) buckets));
	printf("Number of hash map insertions: %d\n", (1 << str_length));
	printf("Number of collisions: %d or %.2f%%\n", collisions, 100 * collisions / (float) (1 << str_length));

	char* user_str = malloc(sizeof(char) * buffer_length);
	assert(user_str);

	while(1) {
		printf("%s\n", "Enter str to see it exists in the power set: ");
		while(1) {
			c = getchar();
			if (c==EOF || c=='\n') {
				proceed=0;
				break;
			}
			if (!isTokenizer(c)) {
				ungetc(c, stdin);
				break;
			}
		}
		if(proceed==0) {
			break;
		}
		i=0;
		while(1) {
			c = getchar();
			if(isTokenizer(c) || c==EOF) {
				user_str[i] = 0;       //terminating 0
				break;
			}
			user_str[i]=c;
			if (i == buffer_length - 1) { // buffer is full
				buffer_length = buffer_length + buffer_length;
				user_str = realloc(user_str, sizeof(char)*buffer_length);
				assert(user_str);
			}
			i++;
		}
		count=0;
		sortStr(user_str,i);
		h = djb2Hash(user_str) % saved_map->size;
		if (saved_map->map[h]) {
			printf("%s\n", "Hash hit! Checking entries...");
			item = saved_map->map[h];
			while(item) {
				printf("Entry #%d : %s",count, item->S);
				if(strncmp(item->S, user_str, item->length)!= 0) {
					printf(" -> %s\n", "not a match...");
				} else {
					printf(" -> %s\n", "match found!");
				}
				count++;
				item=item->next;			
			}
		} else {
			printf("%s\n", "Hash miss, this str could not be found...");
		}
		memset(user_str,0,buffer_length);
	}
	free(user_str);
	return 0;
}

