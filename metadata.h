#ifndef METADATA_H
#define METADATA_H

typedef struct {
    const char *name;
    const char *symbol;
} CategoryValue;

typedef struct {
    const char *name;
    const CategoryValue *values;
    int value_count;
} Feature;

// Value lists
extern const CategoryValue poisonous_values[];
extern const CategoryValue cap_shape_values[];
extern const CategoryValue cap_surface_values[];
extern const CategoryValue cap_color_values[];
extern const CategoryValue bruises_values[];
extern const CategoryValue odor_values[];
extern const CategoryValue gill_attachment_values[];
extern const CategoryValue gill_spacing_values[];
extern const CategoryValue gill_size_values[];
extern const CategoryValue gill_color_values[];
extern const CategoryValue stalk_shape_values[];
extern const CategoryValue stalk_root_values[];
extern const CategoryValue stalk_surface_values[];
extern const CategoryValue stalk_color_values[];
extern const CategoryValue veil_type_values[];
extern const CategoryValue veil_color_values[];
extern const CategoryValue ring_number_values[];
extern const CategoryValue ring_type_values[];
extern const CategoryValue spore_print_color_values[];
extern const CategoryValue population_values[];
extern const CategoryValue habitat_values[];

extern const Feature FEATURES[];

extern const int FEATURE_COUNT;

#endif // METADATA_H