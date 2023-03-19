#include "dots.h"



void init_dot_dyn_array(dot_array &arr)
{
	arr.len = 0;
	arr.cap = 2;
	arr.dots = NULL;
	arr.start_val = 2;
	arr.step = 2;
}


error_category push_dot_back(dot_array_t &arr, dot_t dot)
{
	error_category_t rc = OK;
	if (arr.dots == NULL)
	{
		void *temp;
		temp = malloc(sizeof(dot_t) * arr.start_val);
		if (temp)
		{
			arr.dots = (dot_t *) temp;
			arr.cap = arr.start_val;
		}
		else
			rc = IMPOSSIBLE_TO_ALLOCATE;

	}
	else if (arr.len == arr.cap)
	{
		void *temp;
		temp = realloc(arr.dots,sizeof(dot_t) * arr.cap * arr.step);
		if (temp)
		{
			arr.dots = (dot_t *) temp;
			arr.cap *= arr.step;
		}
		else
			rc = IMPOSSIBLE_TO_ALLOCATE;

	}
	if (rc == OK)
		arr.dots[arr.len++] = dot;
	return rc;
}

void clear_dot_array(dot_array_t &arr)
{
	free(arr.dots);
	arr.len = 0;
	arr.cap = 2;
	arr.dots = NULL;
	arr.start_val = 2;
	arr.step = 2;
}

error_category_t fscanf_dots_count(int &dots_count, FILE *f)
{
	if (fscanf(f,"%d",&dots_count) != 1 || dots_count <= 0)
		return INVALID_INPUT;
	return OK;
}

error_category_t fprintf_dots_count(int dots_count, FILE *f)
{
	if (fprintf(f,"%d",dots_count) < 1)
		return IMPOSSIBLE_TO_OUTPUT;
	return OK;
}


error_category_t fscanf_dots(dot_array_t &dots, FILE *f)
{
	error_category_t rc;
	if (f == NULL)
		return INVALID_FILENAME;
	int dots_count;

	rc = fscanf_dots_count(dots_count, f);
	for (int i = 0;rc == OK &&  i < dots_count; i++)
	{
		dot_t dot;
		rc = fscanf_dot(dot, f);
		if (rc == OK)
			rc = push_dot_back(dots, dot);
	}

	if (rc != OK)
		clear_dot_array(dots);

	return rc;
}

error_category_t fprintf_dots(dot_array_t &dot_array, FILE *f)
{
	error_category_t rc;
	if (f == NULL)
		return INVALID_FILENAME;


	rc = fprintf_dots_count(dot_array.len, f);
	for (int i = 0;rc == OK && i < dot_array.len; i++)
	{
		fprintf(f, "\n");
		rc = fprintf_dot(f, dot_array.dots[i]);
	}


	return rc;
}

int is_empty(dot_array_t &dot_array)
{
	return dot_array.len == 0;
}

int len(dot_array_t &dot_array)
{
	return dot_array.len;
}





