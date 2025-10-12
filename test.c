#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "data.h"
#include "datachain.h"
#include "decisiontree.h"
#include "c0-contracts.h"

void test_libraries() {
    // test data.h
    dataunit_t du = dataunit_new();
    for (int i = 0; i < NFEATURES; i++) {
        printf("Feature %d: %d\n", i, get_nth_feature_val(du, i));
    }
    printf("Label: %d\n", get_label(du));

    // test datachain.h
    datachain_t dc = datachain_new();
    assert(dc != NULL);
    printf("Datachain created successfully.\n");

    // some more complex test
    ENSURES(is_datachain(dc));
    ENSURES(is_dataunit(du));

    free(du);
    datachain_free(dc);
    printf("All ENSURES passed.\n");
}

void test_copy_and_percentyes() {
    datachain_t dc = datachain_new();
    dataunit_t du1 = dataunit_new();
    du1->label = true;
    dataunit_t du2 = dataunit_new();
    du2->label = false;
    dataunit_t du3 = dataunit_new();
    du3->label = true;

    datachain_add(dc, du1);
    datachain_add(dc, du2);
    datachain_add(dc, du3);

    long double percent_yes = datachain_percentyes(dc);
    printf("Percent yes: %.2Lf\n", percent_yes); // Expecting 0.666667
    assert(percent_yes > 0.66 && percent_yes < 0.67);

    datachain_t dc_copy = datachain_copy(dc);
    assert(is_datachain(dc_copy));
    assert(dc_copy->n_elements == dc->n_elements);
    printf("Datachain copied successfully with %d elements.\n", dc_copy->n_elements);

    datachain_free(dc);
    printf("Original datachain freed successfully.\n");
    datachain_free(dc_copy);
    // Note: dataunits are freed within datachain_free
    printf("Datachains freed successfully.\n");
}

void test_decisiontree() {
    // make a new decision tree
    decisiontree_t dt = decisiontree_new(false);
    assert(is_decisiontree(dt));
    printf("Decision tree created successfully.\n");

    // initialize with some data
    datachain_t dc = datachain_new();
    dataunit_t du1 = dataunit_new();
    bool fv1[NFEATURES] = {true, false, true, false, true};
    du1->label = true;
    du1->feature_vals = fv1;

    dataunit_t du2 = dataunit_new();
    bool fv2[NFEATURES] = {false, true, false, true, false};
    du2->label = false;
    du2->feature_vals = fv2;

    dataunit_t du3 = dataunit_new();
    bool fv3[NFEATURES] = {true, true, false, false, true};
    du3->label = true;
    du3->feature_vals = fv3;

    printf("Adding data units to datachain for decision tree initialization.\n");

    datachain_add(dc, du1);
    datachain_add(dc, du2);
    datachain_add(dc, du3);

    printf("Datachain with %d elements created for decision tree initialization.\n", dc->n_elements);
    decisiontree_init(dt, dc, 2);
    assert(is_decisiontree(dt));
    printf("Decision tree initialized successfully.\n");
}

int main() {
    test_libraries();
    test_copy_and_percentyes();
    printf("All tests completed successfully.\n");
    return 0;
}