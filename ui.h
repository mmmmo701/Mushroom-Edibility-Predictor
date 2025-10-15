#ifndef UI_H
#define UI_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "decisiontree.h"
#include "data.h"
#include "metadata.h"

extern int global_n_features;
extern char** feature_names;

void set_global_n_features(int n);
void set_feature_names(char** names);
void query_user(decisiontree_t dt);
int get_max_depth();

#endif
