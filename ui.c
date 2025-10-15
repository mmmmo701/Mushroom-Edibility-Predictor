#include "ui.h"

int global_n_features;
char** feature_names;

void set_global_n_features(int n) {
    global_n_features = n;
}

void set_feature_names(char** names) {
    feature_names = names;
}

bool ask_feature(int feature_index) {
    if(feature_index < 0 || feature_index >= global_n_features) {
        fprintf(stderr, "Invalid feature index: %d\n", feature_index);
        exit(EXIT_FAILURE);
    }
    char response[10];
    while (true) {
        printf("Does the mushroom have the following feature? \n%s (y/n): ", feature_names[feature_index]);
        if (fgets(response, sizeof(response), stdin) != NULL) {
            if (response[0] == 'y' || response[0] == 'Y') {
                return true;
            } else if (response[0] == 'n' || response[0] == 'N') {
                return false;
            } else {
                printf("Invalid input. Please enter 'y' or 'n'.\n");
            }
        } else {
            printf("Error reading input. Please try again.\n");
        }
    }
}

void query_user(decisiontree_t dt) {
    printf("Welcome to the Mushroom Edibility Predictor!\n");
    printf("Please answer the following questions about the mushroom:\n");
    
    if(guess_from_decisiontree(dt)) {
        printf("The mushroom is predicted to be: POISONOUS\n");
    } else {
        printf("The mushroom is predicted to be: EDIBLE\n");
    }
}

int get_max_depth() {
    int mmd;
    printf("Enter the maximum number of questions you want to be asked (tree depth): ");
    scanf("%d", &mmd);
    getchar(); // consume the newline character after the number input
    if(mmd < 0) {
        fprintf(stderr, "Invalid max depth: %d\n", mmd);
        exit(EXIT_FAILURE);
    }
    if(mmd > global_n_features) {
        printf("Warning: max depth %d is greater than number of features %d. Setting max depth to %d.\n", mmd, global_n_features, global_n_features);
        mmd = global_n_features;
    }
    return mmd;
}