# Symbol adressable memory
Located in `memory.h/c`

## Intro
Storing data in an array of type ``` sam_obj**``` with functions for interacting with  symbols instead of regular indexing. The first value in the array is not a pointer but the size that which it will expand by is `sam_alloc()` is called and the array is full. Instead of storing the length of the array a pointer to itself is used as the terminator.

## Data types

### sam_pt
```C 
typedef struct {
    int size;
    int esize;
} sam_pt;
```
Stores relavant infomation about the pointer table

### sam_obj

```C
typedef struct {
    char* symbol;  
    void* data;  
} sam_obj;
```

The data type in which memory objects are stored. Contains `char* symbol` and `void* data`. Data would be expected to store a struct containing further infomation about the type of data and the data itself.

## Methods


### sam_pt_init
```C
int sam_pt_init(sam_pt* spt, int length, int expandSize);
```

Creates a new array and adds the extension size and terminator. Returns the array pointer if sucsessfull, returns a null pointer if malloc has failed.

### sam_alloc
```C
void* sam_alloc(sam_pt* spt, char* symbol, int dsize, void* data);
```

Finds a free pointer in the array `pt` and creates a new `sam_obj` struct. Returns a pointer to `sam_obj.data` is sucsessfull. If the symbol already exists or any `malloc` calls fail it will return a null pointer.

### sam_get_data_ptr
```C
void* sam_get_data_ptr(sam_pt* spt, char* symbol);
```

Returns a pointer to data corrosponding to the symbol.  
Returns a null pointer if the symbol cannot be found.

