#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include "datachain.h"
#include "data.h"

typedef struct decisiontree_header decisiontree;
typedef decisiontree* decisiontree_t;

struct decisiontree_header {
    bool is_leaf;
    int feature; // only valid if is_leaf is false (0 <= feature < NFEATURES)
    decisiontree_t left, right; // left = feature is false, right = feature is true
    bool label; // only valid if is_leaf is true
};

bool is_decisiontree(decisiontree_t x);
decisiontree_t decisiontree_new(bool label);
void decisiontree_init(decisiontree_t x, datachain_t data, int max_depth);
void decisiontree_free(decisiontree_t x);
bool guess_from_decisiontree(decisiontree_t x, dataunit_t d);

#endif
