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



error_category_t fprintf_line(FILE *f_out, line_t &line)
{
	error_category_t err = OK;
	if (f_out == NULL)
		err = INVALID_FILENAME;
	if (fprintf(f_out,"%d %d", line.index_from ,line.index_to) < 2)
		err = INVALID_INPUT;
	return err;
}

error_category_t validate_line(line_t line, int dots_count)
{
	error_category_t rc = OK;
	if (line.index_to >= dots_count || line.index_to < 0 || line.index_from >= dots_count || line.index_from < 0)
		rc = INVALID_INDEX;
	return rc;
}




