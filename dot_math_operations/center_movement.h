#ifndef INC_1_LAB_CENTER_MOVEMENT_H
#define INC_1_LAB_CENTER_MOVEMENT_H


#include "3d_objects/dots.h"

void init_center(dot_t &center);
error_category_t move_dot(dot_t &dot,dot_t &vector);
error_category_t move_dots(dot_array_t &array, dot_t &vector);
dot_t find_center(dot_array_t &array);
error_category_t move_dot_away(dot_t &dot, dot_t &vector);
void reverse_coordinates(dot_t &dot);


#endif //INC_1_LAB_CENTER_MOVEMENT_H
