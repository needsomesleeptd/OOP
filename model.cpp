#include "model.h"


void init_model(model_t &model)
{
	init_center(model.center);
	init_dot_dyn_array(&model.dots);
	init_line_dyn_array(&model.lines);
}

error_category_t fscanf_model(FILE *f_in,model_t &model)
{
	error_category_t rc = OK;
	rc = fscanf_dots(f_in, model.dots);
	if (rc == OK)
		rc = fscanf_lines(f_in,model.lines);
	return rc;
}

void center_model(model_t &model)
{
	center_dots(model.dots,model.center);
}

void rotate_model(model_t &model, rotator_t &rotator)
{
	rotate_dots(model.dots,rotator);
}

void scale_model(model_t &model, scaler_t &scaler)
{
	scale_dots(model.dots,scaler);
}


