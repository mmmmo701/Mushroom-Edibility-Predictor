#include "data.h"

// ------------ data_list --------------

typedef struct datalist_header datalist;
typedef datalist* datalist_t;

struct datalist_header {
    dataunit_t data;
    datalist* next;
}

// ------------ data_chain --------------

typedef struct datachain_header datachain;
typedef datachain* datachain_t;

struct datachain_header {
    datalist_t start, end;
}

datachain_t datachain_new();
