#ifndef INC_1_LAB_SCALER_H
#define INC_1_LAB_SCALER_H

#include "error_handling.h"
#include "3d_objects/dots.h"

struct scaler
{
	double kx;
	double ky;
	double kz;
};

typedef scaler scaler_t;

void scale_dot(dot_t &dot, scaler_t &scaler);
void scale_dots(dot_array &array, scaler_t &scaler);


#endif //INC_1_LAB_SCALER_H
