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

int main() {
    test_libraries();
    printf("All tests completed successfully.\n");
    return 0;
}