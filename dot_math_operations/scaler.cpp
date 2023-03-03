#include "scaler.h"

void scale_dot(dot_t &dot, scaler_t &scaler)
{
	dot.x *= scaler.kx;
	dot.y *= scaler.ky;
	dot.z *= scaler.kz;
}

void scale_dots(dot_array &array, scaler_t &scaler)
{
	for (int i = 0; i < array.len; i++)
		scale_dot(array.dots[i],scaler);

}
