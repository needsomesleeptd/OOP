#include "model.h"
#include <QGraphicsScene>

model_t init_model()
{
	static model_t temp_model;
	init_center(temp_model.center);
	init_dot_dyn_array(temp_model.dots);
	init_line_dyn_array(temp_model.lines);
	return temp_model;
}

void reset_model(model_t &model)
{
	init_center(model.center);
	init_dot_dyn_array(model.dots);
	init_line_dyn_array(model.lines);
}

error_category_t fscanf_model(FILE *f_in,model_t &model)
{
	error_category_t rc = OK;
	model_t temp_model;
	reset_model(temp_model);
	rc = fscanf_dots(f_in, temp_model.dots);
	if (rc == OK)
		rc = fscanf_lines(f_in,temp_model.lines);
	if (rc == OK)
	{
		temp_model.center = calculate_center_model(temp_model);
		clear_model(model);
		model = temp_model;
	}
	else
		clear_model(temp_model);
	return rc;
}

error_category_t fprintf_model(FILE *f_out, model_t &model)
{
	error_category_t rc = OK;
	if (!model.dots.dots)
		rc =  MODEL_NOT_INITIALIZED;
	else
		rc = fprintf_dots(f_out, model.dots);
	if (rc == OK)
	{
		fprintf(f_out,"\n");
		rc = fprintf_lines(f_out, model.lines);
	}
	return rc;
}



error_category_t rotate_model(model_t &model, rotator_t &rotator)
{
	error_category_t rc = OK;
	if (!model.dots.dots)
		rc = MODEL_NOT_INITIALIZED;
	else
		rc = rotate_dots(model.dots,model.center,rotator);
	return rc;
}

error_category_t scale_model(model_t &model, scaler_t &scaler)
{
	error_category_t rc = OK;
	if (!model.dots.dots)
		rc = MODEL_NOT_INITIALIZED;
	else
		rc = scale_dots(model.dots,scaler);
	return rc;
}


dot_t calculate_center_model(model_t &model)
{
	return find_center(model.dots);
}

error_category_t move_model(model_t &model, dot_t &vector)
{
	error_category_t rc = OK;
	if (!model.dots.dots)
		rc = MODEL_NOT_INITIALIZED;
	else
		rc = move_dot(model.center,vector);
	if (rc == OK)
		rc = move_dots(model.dots,vector);
	return rc;
}

error_category_t draw_model(model_t &model, QGraphicsScene *canvas)
{
	error_category_t rc = OK;
	rc = draw_lines(model.lines,model.dots,canvas);
	return rc;

}

void clear_model(model_t &model)
{
	clear_dot_array(model.dots);
	clear_line_array(model.lines);
	init_center(model.center);
}


