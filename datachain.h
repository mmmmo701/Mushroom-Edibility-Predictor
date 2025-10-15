#ifndef DATACHAIN_H
#define DATACHAIN_H

#include "data.h"
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "c0-contracts.h"

// ------------ data_list --------------

typedef struct datalist_header datalist;
typedef datalist* datalist_t;

struct datalist_header {
    dataunit_t data;
    datalist* next;
};

void datalist_free(datalist_t x);

// ------------ data_chain --------------

typedef struct datachain_header datachain;
typedef datachain* datachain_t;

struct datachain_header {
    datalist_t start, end;
    int n_elements;
};

bool is_datachain(datachain_t x);
datachain_t datachain_new();
bool datachain_isempty(datachain_t x);
void datachain_add(datachain_t x, dataunit_t d);
long double datachain_percentyes(datachain_t x);
datachain_t datachain_copy(datachain_t x); 
// note that the copy will share dataunits with the original and reverse the order of elements
void datachain_filter(datachain_t x, int feature, bool value);
void datachain_free(datachain_t x);
void datachain_print(datachain_t x, int max_elements);

#endif