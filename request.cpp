#include "request.h"

void handle_request(request_t request)
{
	static model_t  model = init_model();
	switch (request.type)
	{
		case request::rotate:
			rotate_model(model,request.action.rotator);
			break;

		case request::scale:
			scale_model(model,request.action.scaler);
			break;

		case request::move:
			model.center = request.action.center;
			center_model(model);
			break;

		case request::load_model:
			fscanf_model(request.action.f_pointer, model); //TOdO:: add error handling
			break;
		case request::draw_model:
			draw_model(model,request.action.canvas);
			break;

	}
}