#ifndef DATA_H
#define DATA_H

#include "stdbool.h"

#define NFEATURES 5

struct dataunit_header {
    bool* feature_vals;
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
