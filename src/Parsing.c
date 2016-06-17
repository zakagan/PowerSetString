#include "Parsing.h"

// Checks if a single char is within a string of tokenizers 
int isTokenizer(const char a) {     
	if(strchr("\n \t,.!?\";:()<>{}[]\\/_@#$%%^&*+=|`~",a)) {
		return 1;
	} else {
		return 0;
	}
}
