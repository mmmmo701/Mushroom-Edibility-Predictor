#ifndef DATACHAIN_H
#define DATACHAIN_H

#include "data.h"

// ------------ data_list --------------

typedef struct datalist_header datalist;
typedef datalist* datalist_t;

struct datalist_header {
    dataunit_t data;
    datalist* next;
};

// ------------ data_chain --------------

typedef struct datachain_header datachain;
typedef datachain* datachain_t;

struct datachain_header {
    datalist_t start, end;
    int n_elements;
};

bool is_datachain(datachain_t x);
datachain_t datachain_new();
void datachain_add(datachain_t x, dataunit_t d);
long double datachain_percentyes(datachain_t x);
datachain_t datachain_copy(datachain_t x); 
// note that the copy will share dataunits with the original and reverse the order of elements


#endif