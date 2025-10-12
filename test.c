#include <stdio.h>
#include "data.h"
#include "datachain.h"
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
}

int main() {
    test_libraries();
    test_copy_and_percentyes();
    printf("All tests completed successfully.\n");
    return 0;
}