#include "datachain.h"

// ------------ datalist --------------

void datalist_free(datalist_t x) {
    #ifdef DEBUG
    printf("Freeing datalist node.\n");
    #endif
    if(x == NULL)
        return;
    free(x->next);
    if(x->data != NULL)
        free(x->data);
    free(x);
}

bool is_seq(datalist_t a, datalist_t b) {
    REQUIRES(a != NULL && b != NULL);
    if(a == b)
        return true;
    if(a->next == NULL)
        return false;
    return is_seq(a->next, b);
}

// ------------ datachain --------------

bool is_datachain(datachain_t x) {
    return x!=NULL && x->start != NULL && x->end != NULL && is_seq(x->start, x->end);
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

bool datachain_isempty(datachain_t x) {
    REQUIRES(is_datachain(x));
    return x->n_elements == 0;
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

void datachain_free(datachain_t x) {
    REQUIRES(is_datachain(x));
    free(x->start);
    free(x);
}

void datachain_filter(datachain_t x, int feature, bool value) {
    REQUIRES(is_datachain(x) && 0 <= feature && feature < (x->start->data->n_features));
    datalist_t prev = NULL;
    datalist_t it = x->start;
    while(it != x->end) {
        if(get_nth_feature_val(it->data, feature) != value) {
            // remove this node
            if(prev == NULL) {
                // removing the start node
                x->start = it->next;
                free(it);
                it = x->start;
            } else {
                prev->next = it->next;
                free(it);
                it = prev->next;
            }
            x->n_elements--;
        } else {
            prev = it;
            it = it->next;
        }
    }
    ENSURES(is_datachain(x));
    return;
}

void datachain_print(datachain_t x, int max_elements) {
    REQUIRES(is_datachain(x));
    printf("Datachain with %d elements:\n", x->n_elements);
    int elements_printed = 0;
    for(datalist_t it = x->start; it != x->end; it = it->next) {
        if(elements_printed >= max_elements) {
            printf("... (and %d more elements)\n", x->n_elements - elements_printed);
            break;
        }
        elements_printed++;
        printf("Dataunit: [");
        for(int i = 0; i < it->data->n_features; i++) {
            printf("%d", get_nth_feature_val(it->data, i));
            if(i < it->data->n_features - 1)
                printf(", ");
        }
        printf("], Label: %d\n", get_label(it->data));
    }
}