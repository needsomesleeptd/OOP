#include "model.h"
#include <QGraphicsScene>

model_t init_model()
{
	model_t temp_model;
	init_center(temp_model.center);
	init_dot_dyn_array(temp_model.dots);
	init_line_dyn_array(temp_model.lines);
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

void draw_model(model_t &model, QGraphicsScene &canvas)
{
	for (int i = 0; i < model.lines.len; i++)
	{
		int from_index = model.lines.lines[i].index_from;
		int to_index = model.lines.lines[i].index_to;
		canvas.addLine(model.dots.dots[from_index].x,model.dots.dots[from_index].y,model.dots.dots[to_index].x,model.dots.dots[to_index].y);
	}
}


