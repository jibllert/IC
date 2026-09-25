#include "memory.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void sam_pt_zero(sam_pt* spt) {
    sam_obj** pt = spt->pt;
    for (int i=0; i < spt->size; i++) {
        pt[i]=NULL;
    }
}

int sam_pt_init(sam_pt* spt, int length, int expandSize) {
    printf("PT init\n");
    sam_obj** pt = malloc(length*sizeof(sam_obj*));
    if (pt==NULL) {
        return 1;
    }
    
    if (spt==NULL) {
        return 1;
    }
    spt->esize = expandSize;
    spt->size = length;
    spt->pt = pt;

    sam_pt_zero(spt);
    return 0;
}

int sam_obj_index(sam_pt* spt, char* symbol) {
    sam_obj** pt = spt->pt;
    for (int i=0; i < spt->size; i++) {
        if (pt[i]!=NULL) {
            if (strcmp(pt[i]->symbol, symbol)==0) {
                return i;
            }
        }
    }
    return -1;
}

void* sam_get_data_ptr(sam_pt* spt, char* symbol) {
    int i = sam_obj_index(spt, symbol);
    if (i==-1) {
        return NULL;
    }
    return spt->pt[i]->data;
}

int sam_find_nullpointer(sam_pt* spt) {
    sam_obj** pt = spt->pt;
    for (int i=0; i < spt->size; i++) {
        if (pt[i]==NULL) {
            return i;
        }
    }
    return -1;
}

sam_obj** sam_pt_expand(sam_pt* spt) {
    sam_obj** new = realloc(spt->pt, spt->size + spt->esize);
    if (new==NULL) {
        return NULL;
    }
    return new;
}

void* sam_alloc(sam_pt* spt, char* symbol, int dsize, void* data) {
    printf("PT alloc\n");
    sam_obj** pt = spt->pt;
    if (sam_obj_index(spt, symbol)!=-1) {//Symbol already exists
        return NULL;
    }
    printf("checked pointer already exists\n");
    int npi = sam_find_nullpointer(spt);

    if (npi==-1) {
        printf("no null pointer avalible\n");
        if (sam_pt_expand(spt)==NULL) {
            printf("expand is null\n");
            return NULL;
        }
    }
    npi = sam_find_nullpointer(spt);
    printf("Null pointer found\n");

    pt[npi] = malloc(dsize+strlen(symbol)+1);
    if (pt[npi]==NULL) {
        return NULL;
    }
    pt[npi]->symbol = malloc(strlen(symbol)+1);
    pt[npi]->data = malloc(dsize);
    if (pt[npi]==NULL | pt[npi]==NULL) {
        free(pt[npi]->symbol);
        free(pt[npi]->data);
        return NULL;
    }
    strcpy(pt[npi]->symbol, symbol);
    memcpy(pt[npi]->data, data, dsize);
    return pt[npi]->data;
}

void sam_mop_free(sam_pt* spt, char* symbol) {
    sam_obj** pt = spt->pt;
    int i = sam_obj_index(spt, symbol);
    sam_obj* obj = pt[i];
    free(obj->data);
    free(obj->symbol);
    free(obj);
    pt[i] = NULL;
}