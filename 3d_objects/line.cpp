#include "line.h"

error_category fscanf_line(FILE *f_in, line_t &line)
{
	error_category_t err = OK;
	if (f_in == NULL)
		err = INVALID_FILENAME;
	if (fscanf(f_in,"%d %d", &line.index_from ,&line.index_to) != 2)
		err = INVALID_INPUT;
	return err;
}



error_category fprintf_line(FILE *f_out, line_t &line)
{
	error_category_t err = OK;
	if (f_out == NULL)
		err = INVALID_FILENAME;
	if (fprintf(f_out,"%d %d", line.index_from ,line.index_to) < 2)
		err = INVALID_INPUT;
	return err;
}






