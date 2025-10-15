#include "metadata.h"

// Value lists
const CategoryValue poisonous_values[] = {
    {"edible", "e"}, {"poisonous", "p"}
};

const CategoryValue cap_shape_values[] = {
    {"bell", "b"}, {"conical", "c"}, {"convex", "x"},
    {"flat", "f"}, {"knobbed", "k"}, {"sunken", "s"}
};

const CategoryValue cap_surface_values[] = {
    {"fibrous", "f"}, {"grooves", "g"}, {"scaly", "y"}, {"smooth", "s"}
};

const CategoryValue cap_color_values[] = {
    {"brown", "n"}, {"buff", "b"}, {"cinnamon", "c"}, {"gray", "g"},
    {"green", "r"}, {"pink", "p"}, {"purple", "u"}, {"red", "e"},
    {"white", "w"}, {"yellow", "y"}
};

const CategoryValue bruises_values[] = {
    {"bruises", "t"}, {"no", "f"}
};

const CategoryValue odor_values[] = {
    {"almond", "a"}, {"anise", "l"}, {"creosote", "c"}, {"fishy", "y"},
    {"foul", "f"}, {"musty", "m"}, {"none", "n"}, {"pungent", "p"}, {"spicy", "s"}
};

const CategoryValue gill_attachment_values[] = {
    {"attached", "a"}, {"descending", "d"}, {"free", "f"}, {"notched", "n"}
};

const CategoryValue gill_spacing_values[] = {
    {"close", "c"}, {"crowded", "w"}, {"distant", "d"}
};

const CategoryValue gill_size_values[] = {
    {"broad", "b"}, {"narrow", "n"}
};

const CategoryValue gill_color_values[] = {
    {"black", "k"}, {"brown", "n"}, {"buff", "b"}, {"chocolate", "h"},
    {"gray", "g"}, {"green", "r"}, {"orange", "o"}, {"pink", "p"},
    {"purple", "u"}, {"red", "e"}, {"white", "w"}, {"yellow", "y"}
};

const CategoryValue stalk_shape_values[] = {
    {"enlarging", "e"}, {"tapering", "t"}
};

const CategoryValue stalk_root_values[] = {
    {"bulbous", "b"}, {"club", "c"}, {"cup", "u"}, {"equal", "e"},
    {"rhizomorphs", "z"}, {"rooted", "r"}, {"missing", "?"}
};

const CategoryValue stalk_surface_values[] = {
    {"fibrous", "f"}, {"scaly", "y"}, {"silky", "k"}, {"smooth", "s"}
};

const CategoryValue stalk_color_values[] = {
    {"brown", "n"}, {"buff", "b"}, {"cinnamon", "c"}, {"gray", "g"},
    {"orange", "o"}, {"pink", "p"}, {"red", "e"}, {"white", "w"}, {"yellow", "y"}
};

const CategoryValue veil_type_values[] = {
    {"partial", "p"}, {"universal", "u"}
};

const CategoryValue veil_color_values[] = {
    {"brown", "n"}, {"orange", "o"}, {"white", "w"}, {"yellow", "y"}
};

const CategoryValue ring_number_values[] = {
    {"none", "n"}, {"one", "o"}, {"two", "t"}
};

const CategoryValue ring_type_values[] = {
    {"cobwebby", "c"}, {"evanescent", "e"}, {"flaring", "f"},
    {"large", "l"}, {"none", "n"}, {"pendant", "p"},
    {"sheathing", "s"}, {"zone", "z"}
};

const CategoryValue spore_print_color_values[] = {
    {"black", "k"}, {"brown", "n"}, {"buff", "b"}, {"chocolate", "h"},
    {"green", "r"}, {"orange", "o"}, {"purple", "u"},
    {"white", "w"}, {"yellow", "y"}
};

const CategoryValue population_values[] = {
    {"abundant", "a"}, {"clustered", "c"}, {"numerous", "n"},
    {"scattered", "s"}, {"several", "v"}, {"solitary", "y"}
};

const CategoryValue habitat_values[] = {
    {"grasses", "g"}, {"leaves", "l"}, {"meadows", "m"},
    {"paths", "p"}, {"urban", "u"}, {"waste", "w"}, {"woods", "d"}
};

// Feature list
const Feature FEATURES[] = {
    {"poisonous", poisonous_values, 2},
    {"cap-shape", cap_shape_values, 6},
    {"cap-surface", cap_surface_values, 4},
    {"cap-color", cap_color_values, 10},
    {"bruises", bruises_values, 2},
    {"odor", odor_values, 9},
    {"gill-attachment", gill_attachment_values, 4},
    {"gill-spacing", gill_spacing_values, 3},
    {"gill-size", gill_size_values, 2},
    {"gill-color", gill_color_values, 12},
    {"stalk-shape", stalk_shape_values, 2},
    {"stalk-root", stalk_root_values, 7},
    {"stalk-surface-above-ring", stalk_surface_values, 4},
    {"stalk-surface-below-ring", stalk_surface_values, 4},
    {"stalk-color-above-ring", stalk_color_values, 9},
    {"stalk-color-below-ring", stalk_color_values, 9},
    {"veil-type", veil_type_values, 2},
    {"veil-color", veil_color_values, 4},
    {"ring-number", ring_number_values, 3},
    {"ring-type", ring_type_values, 8},
    {"spore-print-color", spore_print_color_values, 9},
    {"population", population_values, 6},
    {"habitat", habitat_values, 7}
};

const int FEATURE_COUNT = sizeof(FEATURES) / sizeof(FEATURES[0]);
