#include "memory.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/*
*Expanding arrays without reallocation

Array is divided into chunks with pointers stored in a root array.
One of the roots of the chunk size must be 2
In the event that the root array overflows it will be realocated in its entirety

*/

#define PT_INIT_SIZE 1024 // 256 pointers
int ptsize = 0;
MemoryObjectPointer** SymbolTable;
int memerrno;

//SECTION Memory chunk handling

int pt_get_table_index(char* symbol) {
    // 1000 - OK
    // 1001 - Symbol not found
    int i=0;
    printf("get table index started\n");
    while (1) {
        if ((void*)SymbolTable[i]==(void*)SymbolTable) {//End of table reached
            memerrno = ERRNO_PT_GET_TABLE_INDEX_NF;
            return -1;//Symbol not found
        }
        if (SymbolTable[i]!=NULL) { //Somethings there
            printf("Hay-Needle: %s-%s\n", SymbolTable[i]->symbol, symbol);
            if (strcmp(SymbolTable[i]->symbol, symbol)==0) {
                break;
            }
        }
        i++;
    }
    printf("get table index ok\n");
    memerrno = ERRNO_PT_GET_TABLE_INDEX_OK;
    return i;
}


MemoryObjectPointer* pt_get_ptr(char* symbol) {
    int i = pt_get_table_index(symbol);
    if (i==-1) {
        memerrno = ERRNO_PT_GET_PTR_OK;
        return NULL;
    } else {
        memerrno = ERRNO_PT_GET_PTR_NF;
        return SymbolTable[i];
    }
};

int pt_alloc(char* symbol, int dsize, void* data, int isize, void* info) {
    /* return table
    0 - OK
    1 - End of table reached, not expanded
    2 - End of table reached, table realloc'd
    3 - symbol already exists
    */
    printf("pt_alloc called\n");

    if (pt_get_ptr(symbol)!=NULL) {
        memerrno = ERRNO_PT_ALLOC_SP;
        return -1;
    }

    printf("verified symbol has not already been entered\n");

    int i=0;
    while (SymbolTable[i]!=NULL) {
        if ((void*)SymbolTable[i]==(void*)SymbolTable) {//End of table reached
            void* np = realloc(SymbolTable, PT_INIT_SIZE+ptsize);//New pointer
            if (np==NULL) {
                memerrno = ERRNO_PT_ALLOC_RAF;
                return -1;
            } else {
                SymbolTable = np;
                ptsize += PT_INIT_SIZE;
            }
        }
        i++;
    }
    SymbolTable[i] = malloc(sizeof(MemoryObjectPointer));//Allocate for struct
    if (SymbolTable[i]==NULL) {
        memerrno = ERRNO_PT_ALLOC_MF;
        return -1;
    }
    MemoryObjectPointer* mop = SymbolTable[i];
    mop->symbol = malloc(strlen(symbol));//Aloc symbol, info and data
    mop->info = malloc(isize);
    mop->data = malloc(dsize);
    if (mop->symbol==NULL | mop->info==NULL | mop->info==NULL) {
        free(mop->info);//Free all values as some may of completed
        free(mop->data);
        free(mop->symbol);
        free(mop);//Reset entry as allocation failed
        SymbolTable[i] = NULL;
        memerrno = ERRNO_PT_ALLOC_MF;
        return -1;
    }
    memcpy(mop->symbol, symbol, strlen(symbol));//Copy data in
    memcpy(mop->info, info, isize);
    memcpy(mop->data, data, dsize);

    memerrno = ERRNO_PT_ALLOC_OK;
    return 0;//Sucsess
}

void pt_free_mop(MemoryObjectPointer* ptr) {
    free(ptr->info);
    free(ptr->data);
    free(ptr->symbol);
    free(ptr);
}

int pt_free(char* symbol) {
    int i = pt_get_table_index(symbol);
    if (i==-1) {
        memerrno = ERRNO_PT_FREE_NF;
        return -1;
    }
    MemoryObjectPointer* mop = pt_get_ptr(symbol);
    pt_free_mop(mop);
    SymbolTable[i] = NULL;

    memerrno = ERRNO_PT_FREE_OK;
    return 0;
}

int pt_init() {
    SymbolTable = malloc(PT_INIT_SIZE);
    if (SymbolTable==NULL) {
        memerrno = ERRNO_PT_INIT_MF;
        return -1;
    }
  //  SymbolTable[PT_INIT_SIZE/sizeof(MemoryObjectPointer*)] = (void*)SymbolTable;
    ptsize = PT_INIT_SIZE;
    return 0;
}

int pt_reset() {
    int i=0;
    while ((void*)SymbolTable[i]!=(void*)SymbolTable) {
        pt_free_mop(SymbolTable[i]);
        SymbolTable[i] = NULL;
        i++;
    }
    return pt_init();
}



//!SECTION