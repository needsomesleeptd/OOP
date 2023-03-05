#include "request.h"

void handle_request(request_t request)
{
	static model_t  model = init_model();
	error_category_t rc;
	switch (request.type)
	{
		case request::rotate:
			rotate_model(model,request.action.rotator);
			break;

		case request::scale:
			scale_model(model,request.action.scaler);
			break;

		case request::move:
			move_model(model,request.action.vector);
			break;

		case request::load_model:
			clear_model(model);
			rc = fscanf_model(request.action.f_pointer, model);
			handle_error(rc);
			model.center = calculate_center_model(model);
			break;

		case request::draw_model:
			draw_model(model,request.action.canvas);
			break;

		case request::save_model:
			rc = fprintf_model(request.action.f_pointer, model);
			handle_error(rc);
			break;
		case request::clear_model:
			clear_model(model);
			break;
	}

}