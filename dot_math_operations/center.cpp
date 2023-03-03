#include "center.h"

void init_center(dot_t &center)
{
	center.x = 0;
	center.y = 0;
	center.z = 0;
}

void center_dot(dot_t &dot,dot_t &center)
{
	dot.x -= center.x;
	dot.y -= center.y;
	dot.z -= center.z;
}

void center_dots(dot_array_t &array, dot_t &center)
{
	for (int i = 0; i < array.len; i++)
		center_dot(array.dots[i],center);
}

