typedef struct {
    char* symbol;
    void* data;
} sam_obj;

typedef struct {
    int size;
    int esize;
    sam_obj** pt;
} sam_pt;

void sam_pt_zero(sam_pt* spt);
int sam_pt_init(sam_pt* spt, int length, int expandSize);
int sam_obj_index(sam_pt* spt, char* symbol);
void* sam_get_data_ptr(sam_pt* spt, char* symbol);
int sam_find_nullpointer(sam_pt* spt);
sam_obj** sam_pt_expand(sam_pt* spt);
void* sam_alloc(sam_pt* spt, char* symbol, int dsize, void* data);
void sam_mop_free(sam_pt* spt, char* symbol);