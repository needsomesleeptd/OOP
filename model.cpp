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




error_category_t load_model(model_t &model,const char* filename)
{
	FILE *f_in = fopen(filename, "r");
	if (f_in == NULL)
		return INVALID_FILENAME;
	model_t temp_model = init_model();
	error_category_t rc = fscanf_model(temp_model,f_in);
	fclose(f_in);

	bool has_center = true;
	if (rc == INVALID_CENTER_COORDS)
	{
		rc = OK;
		has_center = false;
	}

	if (rc == OK)
	{
		rc = validate_model(temp_model);
		if (rc != OK)
			clear_model(temp_model);
		else
		{
			if (!has_center)
				calculate_center_model(temp_model);
			clear_model(model);
			model = temp_model;
		}
	}

	return  rc;


}

error_category_t save_model(model_t &model,const char* filename)
{
	error_category_t rc;
	FILE *f_out = fopen(filename, "w");
	if (f_out == NULL)
		return INVALID_FILENAME;
	rc = fprintf_model(model,f_out);
	fclose(f_out);
	return rc;

}

error_category_t fscanf_center(dot_t &center, FILE *f_in)
{
	error_category_t rc = OK;
	if (fscanf(f_in,"%lf %lf %lf",&center.x,&center.y,&center.z) != 3)
		rc = INVALID_CENTER_COORDS;

	return rc;
}
error_category_t fscanf_model(model_t &model,FILE *f_in)
{
	error_category_t rc;
	rc = fscanf_dots(model.dots, f_in);
	if (rc == OK)
	{
		rc = fscanf_lines(model.lines, f_in);
		if (rc != OK)
			clear_dot_array(model.dots);
		else
			rc = fscanf_center(model.center,f_in);
	}


	return rc;
}

error_category_t validate_model(model_t &model)
{
	return validate_lines(model.lines,len(model.dots));
}


error_category_t fprintf_center(dot_t &center, FILE *f_in)
{
	error_category_t rc = OK;
	if (fprintf(f_in,"%lf %lf %lf",center.x,center.y,center.z) < 3)
		rc = INVALID_INPUT;

	return rc;
}
error_category_t fprintf_model(model_t &model, FILE *f_out)
{
	error_category_t rc;
	if (is_empty(model.dots))
		rc =  MODEL_NOT_INITIALIZED;
	else
		rc = fprintf_dots(model.dots, f_out);
	if (rc == OK)
	{
		fprintf(f_out,"\n");
		rc = fprintf_lines(model.lines, f_out);
	}
	if (rc == OK)
	{
		fprintf(f_out,"\n");
		rc = fprintf_center(model.center, f_out);
	}
	return rc;
}



error_category_t rotate_model(model_t &model, rotator_t &rotator)
{
	error_category_t rc;
	if (is_empty(model.dots))
		rc = MODEL_NOT_INITIALIZED;
	else
		rc = rotate_dots(model.dots,model.center,rotator);
	return rc;
}

error_category_t scale_model(model_t &model, scaler_t &scaler)
{
	error_category_t rc;
	if (is_empty(model.dots))
		rc = MODEL_NOT_INITIALIZED;
	else
		rc = scale_dots(model.dots,model.center,scaler);
	return rc;
}


void calculate_center_model(model_t &model)
{
	model.center =  find_center(model.dots);
}

error_category_t move_model(model_t &model, dot_t &vector)
{
	error_category_t rc;
	if (is_empty(model.dots))
		rc = MODEL_NOT_INITIALIZED;
	else
		rc = move_dot(model.center,vector);
	if (rc == OK)
		rc = move_dots(model.dots,vector);
	return rc;
}

error_category_t draw_model(model_t &model, QGraphicsScene *canvas)
{
	error_category_t rc;
	rc =  draw_lines(model.lines,model.dots,canvas);
	QPen red_pen(Qt::red);
	red_pen.setWidth(LINE_WIDTH);
	dot_t drawing_center = adjust_dot(model.center,canvas);
	canvas->addEllipse(drawing_center.x,drawing_center.y,5,5,red_pen);
	return rc;
}

error_category_t change_center(model_t &model, dot_t &dot)
{
	model.center = dot;
	return OK;
}
void clear_model(model_t &model)
{
	clear_dot_array(model.dots);
	clear_line_array(model.lines);
	init_center(model.center);
}


