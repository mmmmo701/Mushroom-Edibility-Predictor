#include "data.h"

// ------------ dataunit --------------

bool is_dataunit(dataunit_t x) {
    return x != NULL && x->feature_vals != NULL;
}

dataunit_t dataunit_new(int my_n_features) {
    dataunit_t res = malloc(sizeof(dataunit));
    res->n_features = my_n_features;    
    res->feature_vals = malloc((res->n_features) * (sizeof(bool)));
    for(int i=0;i<(res->n_features);i++)
        res->feature_vals[i] = 0;
    ENSURES(is_dataunit(res));
    return res;
}

bool get_nth_feature_val(dataunit_t x, int n) {
    REQUIRES(is_dataunit(x) && 0<=n && n<(x->n_features));
    return x->feature_vals[n];
}

bool get_label(dataunit_t x) {
    REQUIRES(is_dataunit(x));
    return x->label;
}


