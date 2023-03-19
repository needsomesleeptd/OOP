#include "request.h"

error_category_t handle_request(request_t request)
{
	static model_t  model = init_model();
	error_category_t rc = OK;
	switch (request.type)
	{
		case request::rotate:
            rc = save_model(model,"../.last_change");
			rc = rotate_model(model,request.rotator);
			break;

		case request::scale:
            rc = save_model(model,"../.last_change");
			rc = scale_model(model,request.scaler);
			break;

		case request::move:
            rc = save_model(model,"../.last_change");
			rc  = move_model(model,request.vector);
			break;

		case request::load_model:
			rc = save_model(model,"../.last_change");
			rc = load_model(model,request.filename);
			break;

		case request::draw_model:
			rc = draw_model(model,request.canvas);
			break;

		case request::save_model:
			rc = save_model(model,request.filename);
			break;
		case request::clear_model:
			clear_model(model);
			break;
		case request::revert_changes:
			rc = load_model(model,request.filename);
			if (rc != OK)
				clear_model(model);
			break;
		case request::change_center:
			rc = save_model(model,"../.last_change");
			rc = change_center(model,request.dot);
			break;
		case request::reset_center:
			rc = save_model(model,"../.last_change");
			calculate_center_model(model);
			break;
		default:
			rc = INVALID_COMMAND;

	}
	return rc;

}

