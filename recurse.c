#include <stdio.h>
#include <stdlib.h>

int recurse(int input){ 
	if (input == 0){ 
		return 2;
	}
	return 3*(input-1)+recurse(input-1)+1;
}

int main (int argc, char* argv[]){ 
	int input = atoi(argv[1]);	

	printf("%d\n", recurse(input)); 

	return EXIT_SUCCESS;
}
