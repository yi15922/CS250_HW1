#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

	int input = atoi(argv[1]);

	for (int i = 0; i < input; i++){ 
		printf("%d\n", 7*(i+1));
	}
	return EXIT_SUCCESS;
}
