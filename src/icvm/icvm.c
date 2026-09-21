#include <stdio.h>
#include <string.h>

#include "icvm.h"
#include "structs.h"
#include "memory.h"

int icvm_init() {
    pt_init();
    char* sym = "num1";
    int data = 12345;
    char* info = "infomation";
    pt_alloc(sym, sizeof(int), &data, strlen(info), info);
    int* dptr = pt_get_ptr(sym)->data;
    printf("Retrived data: %d\n", *dptr);
}