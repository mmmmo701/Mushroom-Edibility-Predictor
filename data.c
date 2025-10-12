#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "data.h"
#include "c0-contracts.h"

bool is_dataunit(dataunit_t x) {
    return x != NULL && x->feature_vals != NULL;
}

dataunit_t dataunit_new() {
    dataunit_t res = malloc(sizeof(dataunit));
    res->feature_vals = malloc((NFEATURES) * (sizeof(bool)));
    for(int i=0;i<NFEATURES;i++)
        res->feature_vals[i] = 0;
    ENSURES(is_dataunit(res));
    return res;
}

bool get_nth_feature_val(dataunit_t x, int n) {
    REQUIRES(is_dataunit(x) && 0<=n && n<NFEATURES);
    return x->feature_vals[n];
}

bool get_label(dataunit_t x) {
    REQUIRES(is_dataunit(x));
    return x->label;
}


