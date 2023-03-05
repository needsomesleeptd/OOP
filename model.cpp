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

error_category_t fscanf_model(FILE *f_in,model_t &model)
{
	error_category_t rc = OK;
	rc = fscanf_dots(f_in, model.dots);
	if (rc == OK)
		rc = fscanf_lines(f_in,model.lines);
	return rc;
}

error_category_t fprintf_model(FILE *f_out, model_t &model)
{
	error_category_t rc = OK;
	rc = fprintf_dots(f_out, model.dots);
	if (rc == OK)
	{
		fprintf(f_out,"\n");
		rc = fprintf_lines(f_out, model.lines);
	}
	return rc;
}



void rotate_model(model_t &model, rotator_t &rotator)
{
	rotate_dots(model.dots,model.center,rotator);
}

void scale_model(model_t &model, scaler_t &scaler)
{
	scale_dots(model.dots,scaler);
}


dot_t calculate_center_model(model_t &model)
{
	return find_center(model.dots);
}

void move_model(model_t &model, dot_t &vector)
{
	move_dot(model.center,vector);
	move_dots(model.dots,vector);
}

void draw_model(model_t &model, QGraphicsScene *canvas)
{
	for (int i = 0; i < model.lines.len; i++)
	{
		int from_index = model.lines.lines[i].index_from;
		int to_index = model.lines.lines[i].index_to;
		dot_t dot_from = model.dots.dots[from_index];
		dot_t dot_to = model.dots.dots[to_index];
		dot_from.x += canvas->width() / 2;
		dot_to.x += canvas->width() / 2;
		dot_from.y += canvas->height() / 2;
		dot_to.y += canvas->height() / 2;


		canvas->addLine(dot_from.x,dot_from.y,dot_to.x,dot_to.y);
	}
}

void clear_model(model_t &model)
{
	clear_dot_array(model.dots);
	clear_line_array(model.lines);
	model = init_model();
}


