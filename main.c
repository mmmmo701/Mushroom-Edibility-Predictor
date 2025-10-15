#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "data.h"
#include "datachain.h"
#include "decisiontree.h"
#include "c0-contracts.h"
#include "metadata.h"
#include "ui.h"

int get_total_value_count() {
    int total = 0;
    for (int i = 0; i < FEATURE_COUNT; i++) {
        total += FEATURES[i].value_count;
    }
    return total;
}

datachain_t get_data_from_file(char* filename) {
    datachain_t dc = datachain_new();
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    char line[256];
    char* str_is = " is ";
    while (fgets(line, sizeof(line), file)) {
        dataunit_t du = dataunit_new(global_n_features);
        char *token = strtok(line, ",");
        if(token[0] == 'p')
            du->label = true;
        else
            du->label = false;
        token = strtok(NULL, ",");
        int feature_cnt = 0;
        for(int i=1; token != NULL;i++) {
            for(int j=0; j<FEATURES[i].value_count - 1; j++){
                du->feature_vals[feature_cnt] = (token[0] == FEATURES[i].values[j].symbol[0]);
                size_t len = strlen(FEATURES[i].name) + strlen(str_is) + strlen(FEATURES[i].values[j].name) + 1;
                char *tmp_feature_name = malloc(len);
                if (tmp_feature_name == NULL) exit(1);
                snprintf(
                    tmp_feature_name, len, "%s%s%s",
                    FEATURES[i].name, str_is, FEATURES[i].values[j].name
                );
                feature_names[feature_cnt] = tmp_feature_name;
                feature_cnt++;
            }
            assert(feature_cnt <= global_n_features);
            token = strtok(NULL, ",");
        }
        datachain_add(dc, du);
    }
    return dc;
}

datachain_t get_data() {
    return get_data_from_file("agaricus-lepiota.data");
}

int main() {
    set_global_n_features(get_total_value_count() - FEATURE_COUNT - 1);
    set_feature_names(malloc((global_n_features + 1) * sizeof(char*)));

    datachain_t my_data = get_data();
    decisiontree_t dt = decisiontree_new(false);
    int my_max_depth = get_max_depth();
    
    decisiontree_init(dt, my_data, my_max_depth, calloc((size_t)(global_n_features), sizeof(bool)));

    query_user(dt);
    decisiontree_free(dt);
    datachain_free(my_data); // Note: dataunits are freed within datachain_free
    return 0;
}