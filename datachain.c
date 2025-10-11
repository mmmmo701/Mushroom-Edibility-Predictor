#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include "datachain.h"
#include "c0-contracts.h"

bool is_seq(datalist_t a, datalist_t b) {
    if(a == b)
        return true;
    if(a->next == NULL)
        return false;
    return is_seq(a->next, b);
}

bool is_datachain(datachain_t x) {
    return x->start != NULL && x->end != NULL && is_seq(x->start, x->end);
}

datachain_t datachain_new() {
    datachain_t res = malloc(sizeof(datachain));
    res->start = malloc(sizeof(datalist));
    res->end = res->start;
    ENSURES(is_datachain(res));
    return res;
}
