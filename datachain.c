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
    res->n_elements = 0;
    ENSURES(is_datachain(res));
    ENSURES(res->n_elements == 0);
    return res;
}

void datachain_add(datachain_t x, dataunit_t d) {
    REQUIRES(is_datachain(x) && is_dataunit(d));
    datalist_t newnode = malloc(sizeof(datalist));
    newnode->data = d;
    newnode->next = x->start;
    x->start = newnode;
    x->n_elements++;
    ENSURES(is_datachain(x));
    ENSURES(x->n_elements > 0);
    ENSURES(x->start->data == d);
    return;
}

long double datachain_percentyes(datachain_t x) {
    REQUIRES(x->n_elements > 0);
    int n_tot = x->n_elements;
    int n_yes = 0;

    for(datalist_t it = x->start; it != x->end; it = it->next) {
        // invariant: it is a valid node in the datachain
        if(it->data->label)
            n_yes++;
    }
    return (long double)n_yes / n_tot;
}

datachain_t datachain_copy(datachain_t x) {
    REQUIRES(is_datachain(x));
    datachain_t res = datachain_new();
    for(datalist_t it = x->start; it != x->end; it = it->next) {
        datachain_add(res, it->data);
    }
    ENSURES(is_datachain(res));
    ENSURES(res->n_elements == x->n_elements);
    return res;
}