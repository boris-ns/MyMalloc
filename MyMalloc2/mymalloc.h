#ifndef _MY_MALLOC_H_
#define _MY_MALLOC_H_

#define MEMORY_SIZE 20000 // bytes

typedef struct metadata {
	unsigned int free; // 0 - taken, 1 - free
	unsigned int size;
	struct metadata* next;
} Metadata;

void Init();
void Split(Metadata* block, unsigned int size);
void Merge();
void* Malloc(unsigned int size);
void* Calloc(unsigned int num, unsigned int size);
void* Realloc(void* block, unsigned int newSize);
void Free(void* data);

#endif