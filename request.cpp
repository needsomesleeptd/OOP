#include "request.h"

error_category_t handle_request(request_t request)
{
	static model_t  model = init_model();
	error_category_t rc = OK;
	switch (request.type)
	{
		case request::rotate:
			rc = rotate_model(model,request.action.rotator);
			break;

		case request::scale:
			rc = scale_model(model,request.action.scaler);
			break;

		case request::move:
			rc  = move_model(model,request.action.vector);
			break;

		case request::load_model:
			clear_model(model);
			rc = fscanf_model(request.action.f_pointer, model);
			break;

		case request::draw_model:
			rc = draw_model(model,request.action.canvas);
			break;

		case request::save_model:
			rc = fprintf_model(request.action.f_pointer, model);
			break;
		case request::clear_model:
			clear_model(model);
			break;
		default:
			rc = INVALID_COMMAND;

	}
	return rc;

}