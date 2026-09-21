#ifndef STRUCTS_INCLUDED
#define STRUCTS_INCLUDED

#include "enums.h"

typedef struct {
    int version;
} icbc_header;

typedef struct {
    char* symbol;
    void* info;
    void* data;
} MemoryObjectPointer;

typedef struct {
    builtin_vars VariableType;
    unsigned char Flags;
    void* Value;
} VariableStore;

typedef struct {
    builtin_vars VariableType;
    unsigned char Flags;
    char* Symbol;
    void* InitValue;
} VariableDefiniton;

typedef struct {
    unsigned char DefinitionType;
    void* Definition;
} Definition;

typedef struct {
    bytcodeins Instruction;
    void* body;
} BytecodeInstuction;

#endif