#include "memory.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define ICVM_CHUNK_SIZE 1024
MemoryObject** icvmMemoryObjectsRoot;
int icvmmObjLength;
int icvmObjects;

MemoryObject** GetNextChunk(MemoryObject** pc) {
    if (*(pc+(ICVM_CHUNK_SIZE-sizeof(char*)))==NULL) {
        *(pc+(ICVM_CHUNK_SIZE-sizeof(char*))) = malloc(ICVM_CHUNK_SIZE);
    }
    return (MemoryObject**)(*(pc+(ICVM_CHUNK_SIZE-sizeof(char*))));
} 

int icvm_alloc(char* symbol, int size, void* data) {
    MemoryObject* mobj;
    MemoryObject** icvm_chunk=icvmMemoryObjectsRoot;
    int i=0;
    while (1)
    {
        
        printf("Coutner incremented to %d\n", i);
        if (i==(ICVM_CHUNK_SIZE/sizeof(char*))-1) {
            printf("At end of chunk\n");
            icvm_chunk = GetNextChunk(icvm_chunk-i);
            i=0;
        }
        if (icvm_chunk[i]==0) {
            printf("Free pointer found at %d\n", i);
            icvm_chunk[i] = malloc(sizeof(MemoryObject));
            mobj = icvm_chunk[i];
            break;
        }
        i++;
    }
    printf("Alocating space\n");
    mobj->size = size;
    mobj->data = malloc(size);
    mobj->symbol = malloc(strlen(symbol));
    printf("Copying data\n");
    memcpy(mobj->data, data, size);
    strcpy(mobj->symbol, symbol);
    return 0;
}



void InitMemory() {
    printf("Init Memory\n");
    icvmMemoryObjectsRoot = malloc(ICVM_CHUNK_SIZE);
    printf("Done\n");
}