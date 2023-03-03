//
// Created by Андрей on 03.03.2023.
//

#ifndef INC_1_LAB_REQUEST_H
#define INC_1_LAB_REQUEST_H

#include "model.h"


struct request
{
	enum
	{
		rotate,
		scale,
		move,
		load_model
	} type;

	union
	{
		rotator_t rotator;
		dot_t center;
		scaler_t scaler;
		FILE *f;
	} action;

};

typedef request request_t;

#endif //INC_1_LAB_REQUEST_H
