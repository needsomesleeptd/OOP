#include "dots.h"



void init_dot_dyn_array(dot_array &arr)
{
	arr.len = 0;
	arr.cap = 0;
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
		if (!temp)
			rc = IMPOSSIBLE_TO_ALLOCATE;
		else
		{
			arr.dots = (dot_t *) temp;
			arr.cap = arr.start_val;
		}

	}
	else if (arr.len == arr.cap)
	{
		void *temp;
		temp = realloc(arr.dots,sizeof(dot_t) * arr.cap * arr.step);
		if (!temp)
			rc = IMPOSSIBLE_TO_ALLOCATE;
		else
		{
			arr.dots = (dot_t *) temp;
			arr.cap *= arr.step;
		}

	}
	arr.dots[arr.len++] = dot;
	return rc;
}

void clear_dot_array(dot_array_t &arr)
{
	free(arr.dots);
	init_dot_dyn_array(arr);
}



error_category_t fscanf_dots(FILE *f,dot_array_t &dots)
{
	error_category_t rc = OK;
	if (f == NULL)
		rc =  INVALID_FILENAME;
	int dots_count;
	if (fscanf(f,"%d",&dots_count) != 1)
		rc =  INVALID_INPUT;
	for (int i = 0; i < dots_count; i++)
	{
		dot_t dot;
		if ((rc = fscanf_dot(f,dot)) != OK)
		{
			clear_dot_array(dots);
			break;
		}

	}
	return rc;
}



