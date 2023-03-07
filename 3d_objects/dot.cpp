#include "dot.h"
#include "error_handling.h"


error_category fscanf_dot(FILE *f_in, dot_t &dot)
{
	error_category_t err = OK;
	if (f_in == NULL)
		err = INVALID_FILENAME;
	if (fscanf(f_in,"%lf %lf %lf", &dot.x, &dot.y, &dot.z) != 3)
		err = INVALID_INPUT;
	return err;
}

error_category fprintf_dot(FILE *f_out,dot_t  &dot)
{
	error_category_t err = OK;
	if (f_out == NULL)
		err = INVALID_FILENAME;
	if (fprintf(f_out,"%lf %lf %lf", dot.x, dot.y, dot.z) < 3)
		err = INVALID_INPUT;
	return err;
}










