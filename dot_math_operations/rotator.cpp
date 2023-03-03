#include <cmath>
#include "rotator.h"

double to_radians(double angle_degrees)
{
	double PI = std::acos(-1);
	return angle_degrees*PI/180.0;  //converting from degrees to radians
}


void rotate_OX_dot(dot_t &dot, rotator_t &rotator)
{
	double cos_val = cos(to_radians(rotator.ox));
	double sin_val = sin(to_radians(rotator.ox));

	double save_y = dot.y;

	dot.y = dot.y  * cos_val + dot.z * sin_val;
	dot.z = save_y * -sin_val + dot.z  * cos_val;

}

void  rotate_OY_dot(dot_t &dot, rotator_t &rotator)
{
	double cos_val = cos(to_radians(rotator.oy));
	double sin_val = sin(to_radians(rotator.oy));

	double save_x = dot.x;

	dot.x = dot.x * cos_val - dot.z * sin_val;
	dot.z = save_x * sin_val + dot.z * cos_val;
}

void  rotate_OZ_dot(dot_t &dot, rotator_t &rotator)
{
	double cos_val = cos(to_radians(rotator.oz));
	double sin_val = sin(to_radians(rotator.oz));

	double save_x = dot.x;

	dot.x = dot.x * cos_val + dot.y * sin_val;
	dot.y = save_x * -sin_val + dot.y * cos_val;
}

void rotate_dot(dot_t &dot, rotator_t &rotator)
{
	rotate_OX_dot(dot,rotator);
	rotate_OY_dot(dot,rotator);
	rotate_OZ_dot(dot,rotator);
}

void rotate_dots(dot_array_t array, rotator_t &rotator)
{
	for (int i = 0; i < array.len; i++)
		rotate_dot(array.dots[i],rotator);
}