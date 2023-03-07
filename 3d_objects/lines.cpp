#include "lines.h"

void init_line_dyn_array(line_array &arr)
{
	arr.len = 0;
	arr.cap = 2;
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


error_category_t fscanf_lines(FILE *f,line_array_t &lines)
{
	error_category_t rc = OK;
	if (f == NULL)
		rc =  INVALID_FILENAME;
	int lines_count;
	if (rc == OK && fscanf(f,"%d",&lines_count) != 1)
		rc =  INVALID_INPUT;
	if (rc == OK)
	{
		for (int i = 0; i < lines_count &&  rc == OK; i++)
		{
			line_t line;
			rc = fscanf_line(f, line);
			if (rc != OK)
			{
				clear_line_array(lines);
				break;
			}
			else
				rc = push_line_back(lines, line);
		}
	}
	return rc;
}

error_category_t fprintf_lines(FILE *f,line_array_t &line_array)
{
	error_category_t rc = OK;
	if (f == NULL)
		rc =  INVALID_FILENAME;

	if (rc == OK  && (fprintf(f,"%d",line_array.len) < 1 || line_array.len <= 0))
		rc =  INVALID_INPUT;
	if (rc == OK)
	{
		for (int i = 0; i < line_array.len && rc == OK; i++)
		{
			fprintf(f, "\n");
			rc = fprintf_line(f, line_array.lines[i]);
		}
	}
	return rc;
}

