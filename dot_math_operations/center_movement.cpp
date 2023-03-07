#include "center_movement.h"

void init_center(dot_t &center)
{
	center.x = 0;
	center.y = 0;
	center.z = 0;
}

void move_dot(dot_t &dot,dot_t &vector)
{
	dot.x += vector.x;
	dot.y += vector.y;
	dot.z += vector.z;
}

void move_dots(dot_array_t &array, dot_t &vector)
{
	for (int i = 0; i < array.len; i++)
		move_dot(array.dots[i],vector);
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

