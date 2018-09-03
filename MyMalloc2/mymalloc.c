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
	Metadata* node = metadataList;

	while (node->next != NULL)
	{
		if (node->free == 1 && node->next->free == 1)
		{
			node->size = node->size + node->next->size + sizeof(Metadata);
			node->next = node->next->next;
		}

		node = node->next;
	}
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
	return Malloc(num * size);
}

void* Realloc(void* block, unsigned int newSize)
{
	// @TODO: implement this
}

void Free(void* data)
{
	if (data < memory && data > memory + MEMORY_SIZE)
	{
		printf("Error. Address out of the range.");
		return;
	}

	Metadata* node = (Metadata*) data - sizeof(Metadata);
	node->free = 1;
	Merge();
}