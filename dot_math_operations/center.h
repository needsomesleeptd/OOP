//
// Created by Андрей on 03.03.2023.
//

#ifndef INC_1_LAB_CENTER_H
#define INC_1_LAB_CENTER_H


#include "dots.h"

void init_center(dot_t &center);
void move_dot(dot_t &dot,dot_t &vector);
void move_dots(dot_array_t &array, dot_t &vector);
dot_t find_center(dot_array_t &array);



#endif //INC_1_LAB_CENTER_H
