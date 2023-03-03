#include "lines.h"

void init_line_dyn_array(line_array &arr)
{
	arr.len = 0;
	arr.cap = 0;
	arr.lines = NULL;
	arr.start_val = 2;
	arr.step = 2;
}


error_category push_line_back(line_array_t &arr, line_t line)
{
	error_category_t rc = OK;
	if (arr.lines == NULL)
	{
		void *temp;
		temp = malloc(sizeof(line_t) * arr.start_val);
		if (!temp)
			rc = IMPOSSIBLE_TO_ALLOCATE;
		else
		{
			arr.lines = (line_t *) temp;
			arr.cap = arr.start_val;
		}

	}
	else if (arr.len == arr.cap)
	{
		void *temp;
		temp = realloc(arr.lines,sizeof(line_t) * arr.cap * arr.step);
		if (!temp)
			rc = IMPOSSIBLE_TO_ALLOCATE;
		else
		{
			arr.lines = (line_t *) temp;
			arr.cap *= arr.step;
		}

	}
	arr.lines[arr.len++] = line;
	return rc;
}

void clear_line_array(line_array_t &arr)
{
	free(arr.lines);
	init_line_dyn_array(arr);
}


