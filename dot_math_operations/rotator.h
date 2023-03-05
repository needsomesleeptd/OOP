

#ifndef INC_1_LAB_ROTATOR_H
#define INC_1_LAB_ROTATOR_H


#include "error_handling.h"
#include "dots.h"

struct rotator
{
	double oz;
	double ox;
	double oy;
};

typedef rotator rotator_t;


void rotate_dot(dot_t &dot, dot_t &center_of_rotation, rotator_t &rotator);
void rotate_dots(dot_array_t array, dot_t &center_of_rotation, rotator_t &rotator);
double to_radians(double angle_degrees);







#endif //INC_1_LAB_ROTATOR_H
