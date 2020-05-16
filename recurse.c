#include <stdio.h>
#include <stdlib.h>

int recurse(int input){ 
	if (input == 0){ 
		return 2;
	}
	int result = 3*(input-1)+recurse(input-1)+1;
	printf("%d\n", result); 

	return result;
}


int main (int argc, char* argv[]){ 
	int input = atoi(argv[1]);	
	int result = recurse(input); 

	printf("%d\n", result); 

	return EXIT_SUCCESS;
}
