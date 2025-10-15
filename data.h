#ifndef DATA_H
#define DATA_H

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "c0-contracts.h"

struct dataunit_header {
    bool* feature_vals;
    int n_features;
    bool label;
};

typedef struct dataunit_header dataunit;
typedef dataunit* dataunit_t;

bool is_dataunit(dataunit_t x);
dataunit_t dataunit_new();
bool get_nth_feature_val(dataunit_t x, int n);
bool get_label(dataunit_t x);
void dataunit_free(dataunit_t x);

#endif
