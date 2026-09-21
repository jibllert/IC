#define MEMORY_CHUNK_AVALIBLE = (MEMORY_CHUNK_SIZE - sizeof(char*))
#define MEMORY_CHUNK_SIZE 1024
#include "structs.h"

void InitMemory();

#define ERRNO_PT_GET_TABLE_INDEX_OK 1000 //OK
#define ERRNO_PT_GET_TABLE_INDEX_NF 1001 //Not found
int pt_get_table_index(char* symbol); //Get index from symbol table

#define ERRNO_PT_GET_PTR_OK 1010 //OK
#define ERRNO_PT_GET_PTR_NF 1011 //Not found
MemoryObjectPointer* pt_get_ptr(char* symbol); // Get pointer of MemoryObjectStruct

#define ERRNO_PT_ALLOC_OK 1020 //OK
#define ERRNO_PT_ALLOC_SP 1021 //Symbol already present
#define ERRNO_PT_ALLOC_EOT 1022 //End of table reached, symbol table not realloc'd
#define ERRNO_PT_ALLOC_RAF 1023 //Pointer table realloc failed
#define ERRNO_PT_ALLOC_MF 1024 //Malloc failed when either allocating struct/symbol/info or data
int pt_alloc(char* symbol, int dsize, void* data, int isize, void* info); // Allocate new object to memory

#define ERRNO_PT_FREE_OK 1030 //OK
#define ERRNO_PT_FREE_NF 1031 //Symbol not found
int pt_free(char* symbol); // Free memory object

void pt_free_mop(MemoryObjectPointer* ptr);

#define ERRNO_PT_INIT_OK 1040 //OK
#define ERRNO_PT_INIT_MF 1041 //Malloc fail
int pt_init();