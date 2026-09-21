#define MEMORY_CHUNK_AVALIBLE = (MEMORY_CHUNK_SIZE - sizeof(char*))
#define MEMORY_CHUNK_SIZE 1024
#include "structs.h"

void InitMemory();
int icvm_alloc(char* symbol, int size, void* data);
extern MemoryObject** icvmMemoryObjectsRoot;