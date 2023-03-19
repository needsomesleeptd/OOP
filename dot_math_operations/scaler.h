#ifndef INC_1_LAB_SCALER_H
#define INC_1_LAB_SCALER_H

#include <cmath>

#include "error_handling.h"
#include "3d_objects/dots.h"

struct scaler
{
	double kx;
	double ky;
	double kz;
};

typedef scaler scaler_t;

error_category_t scale_dot(dot_t &dot, dot_t &center, scaler_t &scaler);
error_category_t scale_dots(dot_array &array, dot_t &center, scaler_t &scaler);

#endif //INC_1_LAB_SCALER_H
