#include "model.h"


void init_model(model_t &model)
{
	init_center(model.center);
	init_dot_dyn_array(&model.dots);
	init_line_dyn_array(&model.lines);
}

error_category_t read_model(model_t &model, FILE *f)
{
	if (f == NULL)
		return INVALID_FILENAME;
	int dots_count;
	if (fscanf(f,"%d",&dots_count) != 1)
		return INVALID_INPUT;


}