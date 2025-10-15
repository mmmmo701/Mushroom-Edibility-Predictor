#include "decisiontree.h"

bool is_decisiontree(decisiontree_t x) {
    if(!x->is_leaf && (x->left == NULL || x->right == NULL))
        return false;
    return true;
}

void decisiontree_free(decisiontree_t x) {
    if(x == NULL)
        return;
    if(!x->is_leaf) {
        decisiontree_free(x->left);
        decisiontree_free(x->right);
    }
    free(x);
}

decisiontree_t decisiontree_new(bool label) {
    decisiontree_t res = malloc(sizeof(decisiontree));
    res->is_leaf = true;
    res->feature = 0;
    res->left = NULL;
    res->right = NULL;
    res->label = label;
    ENSURES(is_decisiontree(res));
    return res;
}

void decisiontree_init(decisiontree_t x, datachain_t data, int max_depth, bool* used_features) {
    /*
    time complexity: O(N * D * log(N)) where N = number of dataunits, D = number of features
    space complexity: O(D) for recursion stack
    time complexity is too big for large N, but should be fine for small N
    */
    /*  
    REQUIRES(is_decisiontree(x));
    REQUIRES(is_datachain(data));
    REQUIRES(data->n_elements > 0);
    REQUIRES(max_depth >= 0);
    */
    #ifdef DEBUG_2
    printf("Initializing decision tree node. is_leaf: %d, data size: %d, max_depth: %d\n", x->is_leaf, data->n_elements, max_depth);
    #endif
    REQUIRES(x->is_leaf);

    if(datachain_percentyes(data) == 0 || datachain_percentyes(data) == 1) {
        x->label = (datachain_percentyes(data) == 1);
        return;
    }
    if(max_depth == 0) {
        x->label = (datachain_percentyes(data) >= 0.5);
        return;
    }

    long double best_score = 0; // score = 2 * correct rate
    int best_feature = 0;
    for(int i=0;i<(data->start->data->n_features);i++) {
        if(used_features[i])
            continue;
        datachain_t f_data = datachain_copy(data);
        datachain_filter(f_data, i, false);
        #ifdef DEBUG
        printf("  Evaluating feature %d: false branch size %d\n", i, f_data->n_elements);
        #endif
        datachain_t t_data = datachain_copy(data);
        #ifdef DEBUG
        printf("  Evaluating feature %d: true branch size %d\n", i, t_data->n_elements);
        #endif
        datachain_filter(t_data, i, true);
        if(datachain_isempty(f_data) || datachain_isempty(t_data))
            continue;
        long double f_percent_yes = datachain_percentyes(f_data);
        long double t_percent_yes = datachain_percentyes(t_data);
        long double f_score = (f_percent_yes >= 0.5) ? f_percent_yes : (1 - f_percent_yes);
        long double t_score = (t_percent_yes >= 0.5) ? t_percent_yes : (1 - t_percent_yes);
        assert(f_score >= 0.5);
        assert(t_score >= 0.5);
        assert(f_score <= 1);
        assert(t_score <= 1);
        long double cur_score = 2 * (f_score * (f_data->n_elements) + t_score * (t_data->n_elements)) / (data->n_elements);
        datachain_free(f_data);
        datachain_free(t_data);
        if(cur_score > best_score) {
            best_score = cur_score;
            best_feature = i;
        }
    }

    datachain_t final_f_data = datachain_copy(data);
    datachain_filter(final_f_data, best_feature, false);
    datachain_t final_t_data = datachain_copy(data);
    datachain_filter(final_t_data, best_feature, true);

    x->is_leaf = false;
    x->left = decisiontree_new(0);
    x->right = decisiontree_new(0);
    x->feature = best_feature;
    used_features[best_feature] = true;
    decisiontree_init(x->left, final_f_data, max_depth - 1, used_features);
    decisiontree_init(x->right, final_t_data, max_depth - 1, used_features);

    datachain_free(final_f_data);
    datachain_free(final_t_data);
    ENSURES(is_decisiontree(x));
}

extern bool ask_feature(int feature_index);

bool guess_from_decisiontree(decisiontree_t x) {
    if(x->is_leaf)
        return x->label;
    bool feature_val = ask_feature(x->feature);
    if(feature_val)
        return guess_from_decisiontree(x->right);
    else
        return guess_from_decisiontree(x->left);
}

void decisiontree_print(decisiontree_t x, int depth) {
    if(x == NULL)
        return;
    for(int i=0;i<depth;i++)
        printf("  ");
    if(x->is_leaf) {
        printf("Leaf: label = %s\n", x->label ? "yes" : "no");
    } else {
        printf("Node: feature %d\n", x->feature);
        decisiontree_print(x->left, depth + 1);
        decisiontree_print(x->right, depth + 1);
    }
}
