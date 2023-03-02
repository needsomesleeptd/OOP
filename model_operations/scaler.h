//
// Created by Андрей on 02.03.2023.
//

#ifndef INC_1_LAB_SCALER_H
#define INC_1_LAB_SCALER_H

#include "error_handling.h"
#include "dots.h"

struct scaler
{
	double kx;
	double ky;
	double kz;
};

typedef scaler scaler_t;


#endif //INC_1_LAB_SCALER_H
