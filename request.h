//
// Created by Андрей on 03.03.2023.
//

#ifndef INC_1_LAB_REQUEST_H
#define INC_1_LAB_REQUEST_H

#include <string>

#include "model.h"



struct request
{

	enum
	{
		rotate,
		scale,
		move,
		load_model,
		draw_model,
		save_model,
		clear_model,
		revert_changes,
		change_center,
		reset_center
	} type;

	union
	{
		rotator_t rotator;
		dot_t vector;
		scaler_t scaler;
		const char* filename;
		QGraphicsScene *canvas;
		dot_t dot;
	};
};

typedef request request_t;

error_category_t handle_request(request_t request);


#endif //INC_1_LAB_REQUEST_H
