#include "mymalloc.h"
#include <stdio.h>

char memory[MEMORY_SIZE];
Metadata* metadataList = (void*)memory;


void Init()
{
	metadataList->free = 1;
	metadataList->size = MEMORY_SIZE - sizeof(Metadata);
	metadataList->next = NULL;
}

void Split(Metadata* block, unsigned int size)
{
	Metadata* newBlock = block + sizeof(Metadata) + size; // @TODO: cast to void* void* ?
	newBlock->free = 1;
	newBlock->size = block->size - size - sizeof(Metadata);
	newBlock->next = block->next;

	block->size = size;
	block->free = 0;
	block->next = newBlock;
}

void Merge()
{
	// @TODO: implement this
}

void* Malloc(unsigned int size)
{
	if (metadataList->size == 0)
		Init();

	Metadata* node = metadataList;
	void* result = NULL;
	
	// First-fit
	while (node->next != NULL)
	{
		if (node->size >= size && node->free == 1)
			break;

		node = node->next;
	}

	if (node->size == size)
	{
		node->free = 0;
		result = node + sizeof(Metadata);
	}
	else if (node->size > size + sizeof(Metadata))
	{
		Split(node, size);
		result = node + sizeof(Metadata);
	}

	return result;
}

void* Calloc(unsigned int num, unsigned int size)
{
	// @TODO: implement this
}

void* Realloc(void* block, unsigned int newSize)
{
	// @TODO: implement this
}

void Free(void* data)
{
	// @TODO: implement this
}