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


		if (temp)
		{
			arr.lines = (line_t *)temp;
			arr.cap = arr.start_val;
		}
		else
			rc = IMPOSSIBLE_TO_ALLOCATE;

	}
	else if (arr.len == arr.cap)
	{
		void *temp;
		temp = realloc(arr.lines,sizeof(line_t) * arr.cap * arr.step);

		if (temp)
		{
			arr.lines = (line_t *)temp;
			arr.cap *= arr.step;
		}
		else
			rc = IMPOSSIBLE_TO_ALLOCATE;

	}

	if (rc == OK)
		arr.lines[arr.len++] = line;
	return rc;
}

error_category_t fscanf_lines_count(int &lines_count, FILE *f)
{
	if (fscanf(f,"%d",&lines_count) != 1 || lines_count <= 0)
		return INVALID_INPUT;
	return OK;
}

void clear_line_array(line_array_t &arr)
{
	free(arr.lines);
	arr.len = 0;
	arr.cap = 2;
	arr.lines = NULL;
	arr.start_val = 2;
	arr.step = 2;
}


error_category_t fscanf_lines(line_array_t &lines, FILE *f)
{
	error_category_t rc;
	if (f == NULL)
		return INVALID_FILENAME;
	int lines_count;
	rc = fscanf_lines_count(lines_count,f);
	if (rc == OK)
	{
		for (int i = 0;rc == OK && i < lines_count; i++)
		{
			line_t line;
			rc = fscanf_line(f, line);
			if (rc == OK)
				rc = push_line_back(lines, line);
		}
	}
	if (rc != OK)
		clear_line_array(lines);
	return rc;
}

error_category_t fprintf_lines_count(int lines_count, FILE *f)
{
	if (fprintf(f,"%d",lines_count) < 1)
		return IMPOSSIBLE_TO_OUTPUT;
	return OK;
}

error_category_t fprintf_lines(line_array_t &line_array, FILE *f)
{
	error_category_t rc;
	if (f == NULL)
		return INVALID_FILENAME;

	rc = fprintf_lines_count(line_array.len,f);
	if (rc == OK)
	{
		for (int i = 0;rc == OK && i < line_array.len; i++)
		{
			fprintf(f, "\n");
			rc = fprintf_line(f, line_array.lines[i]);
		}
	}
	return rc;
}


error_category_t validate_lines(line_array_t &line_array, int dots_count)
{
	error_category_t rc = OK;
	for (int i = 0; rc == OK && i < line_array.len; i++)
		rc = validate_line(line_array.lines[i],dots_count);
	return rc;
}


