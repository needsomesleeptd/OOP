#include <cmath>
#include "rotator.h"



static double to_radians(double angle_degrees)
{
	double PI = std::acos(-1);
	return angle_degrees*PI/180.0;  //converting from degrees to radians
}





static error_category_t rotate_OX_dot(dot_t &dot, rotator_t &rotator)
{
	double cos_val = cos(to_radians(rotator.ox));
	double sin_val = sin(to_radians(rotator.ox));

	double save_y = dot.y;

	dot.y = (dot.y)  * cos_val + (dot.z) * sin_val;
	dot.z = (save_y) * -sin_val + (dot.z) * cos_val;
	return OK;

}

static error_category_t   rotate_OY_dot(dot_t &dot, rotator_t &rotator)
{
	double cos_val = cos(to_radians(rotator.oy));
	double sin_val = sin(to_radians(rotator.oy));

	double save_x = dot.x;

	dot.x = (dot.x) * cos_val - (dot.z) * sin_val;
	dot.z = (save_x) * sin_val + (dot.z) * cos_val;
	return OK;
}

static error_category_t   rotate_OZ_dot(dot_t &dot, rotator_t &rotator)
{
	double cos_val = cos(to_radians(rotator.oz));
	double sin_val = sin(to_radians(rotator.oz));

	double save_x = dot.x;

	dot.x = (dot.x) * cos_val + (dot.y) * sin_val;
	dot.y = (save_x) * -sin_val + (dot.y) * cos_val;
	return OK;
}


error_category_t  rotate_dot(dot_t &dot, dot_t &center_of_rotation, rotator_t &rotator)
{
	error_category_t rc = OK;
	substact_coordinates(dot, center_of_rotation);

	rc = rotate_OX_dot(dot,rotator);
	if (rc == OK)
		rc = rotate_OY_dot(dot,rotator);
	if (rc == OK)
		rc = rotate_OZ_dot(dot,rotator);

	add_coordinates(dot,center_of_rotation);
	return rc;
}

error_category_t  rotate_dots(dot_array_t array, dot_t &center_of_rotation, rotator_t &rotator)
{
	error_category_t rc = OK;
	for (int i = 0; rc == OK && i < array.len; i++)
		rc = rotate_dot(array.dots[i], center_of_rotation,rotator);
	return rc;
}