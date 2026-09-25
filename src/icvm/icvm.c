#include <stdio.h>
#include <string.h>

#include "icvm.h"
//#include "structs.h"
#include "memory.h"

#define NMSPC_START_SIZE 0xff
#define NMSPC_EXPAND_SIZE 0xff
sam_pt nmspc_ord;

int icvm_init() {
    sam_pt_init(&nmspc_ord, NMSPC_START_SIZE, NMSPC_EXPAND_SIZE);
    char* symbol = "num1";
    int data = 12345;
    sam_alloc(&nmspc_ord, symbol, sizeof(data), &data);
    int* dp = sam_get_data_ptr(&nmspc_ord, symbol);
    if (dp==NULL) {
        printf("Null pointer from get data ptr\n");
    } else {
        printf("Data: %d\n", *dp);
    }
   
}