#ifndef INC_1_LAB_ROTATOR_H
#define INC_1_LAB_ROTATOR_H


#include "error_handling.h"
#include "3d_objects/dots.h"
#include "center_movement.h"

struct rotator
{
	double oz;
	double ox;
	double oy;
};

typedef rotator rotator_t;


error_category_t  rotate_dot(dot_t &dot, dot_t &center_of_rotation, rotator_t &rotator);
error_category_t  rotate_dots(dot_array_t array, dot_t &center_of_rotation, rotator_t &rotator);









#endif //INC_1_LAB_ROTATOR_H
