#include <stdio.h>
#include "mymalloc.h"

int main()
{
	printf("=== MyMalloc ===\n");

	int* block1 = (int*)Malloc(sizeof(int));
	*block1 = 4;
	printf("Block1 allocated at address: %d, Data: %d\n", block1, *block1);

	float* block2 = (float*)Malloc(sizeof(float));
	*block2 = 2.3;
	printf("Block2 allocated at address: %d, Data %f\n", block2, *block2);

	void* block3 = Malloc(400);
	printf("Block3 allocated at address: %d\n", block3);

	Free(block2);

	int* block4 = (int*)Realloc(block1, 4 * sizeof(int));
	printf("Block3 allocated at address: %d, Data: %d\n", block4, *block4);

	return 0;
}