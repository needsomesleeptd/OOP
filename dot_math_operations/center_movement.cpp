#include "center_movement.h"

void init_center(dot_t &center)
{
	center.x = 0;
	center.y = 0;
	center.z = 0;
}

error_category_t move_dot(dot_t &dot,dot_t &vector)
{
	dot.x += vector.x;
	dot.y += vector.y;
	dot.z += vector.z;
	return OK;
}

void reverse_coordinates(dot_t &dot)
{
	dot.x *= -1;
	dot.y *= -1;
	dot.z *= -1;
}

void substact_coordinates(dot_t &first, dot_t &second)
{
	first.x -= second.x;
	first.y -= second.y;
	first.z -= second.z;
}

void add_coordinates(dot_t &first, dot_t &second)
{
	first.x += second.x;
	first.y += second.y;
	first.z += second.z;
}

error_category_t move_dots(dot_array_t &array, dot_t &vector)
{
	error_category_t rc = OK;
	for (int i = 0; rc == OK && i < array.len; i++)
		rc = move_dot(array.dots[i],vector);
	return rc;
}

dot_t find_center(dot_array_t &array)
{
	dot_t center = {0.0, 0.0, 0.0};
	for (int i = 0; i < array.len; i++)
	{
		center.x += array.dots[i].x;
		center.y += array.dots[i].y;
		center.z += array.dots[i].z;
	}
	center.x /= array.len;
	center.y /= array.len;
	center.z /= array.len;
	return center;
}

