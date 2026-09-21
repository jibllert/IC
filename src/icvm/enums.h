#ifndef ENUMS_DEFINED
#define ENUMS_DEFINED

typedef enum : unsigned char {
    bytecodeins_Definition
} bytcodeins;

typedef enum : unsigned char{
    builtin_vars_bool,
    builtin_vars_char,
    builtin_vars_short,
    builtin_vars_int,
    builtin_vars_long
} builtin_vars;

typedef enum : unsigned char{
    bytecode_deftyp_Variable,
    bytecode_deftyp_Function
} bytecode_deftyp;

#endif
