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
	if (rc == OK && (fscanf(f,"%d",&dots_count) != 1 || dots_count <= 0))
		rc =  INVALID_INPUT;
	if (rc == OK)
	{
		for (int i = 0; i < dots_count &&  rc == OK; i++)
		{
			dot_t dot;
			rc = fscanf_dot(f, dot);
			if (rc != OK)
			{
				clear_dot_array(dots);
				break;
			}
			else
				rc = push_dot_back(dots, dot);
		}
	}
	return rc;
}

error_category_t fprintf_dots(FILE *f,dot_array_t &dot_array)
{
	error_category_t rc = OK;
	if (f == NULL)
		rc =  INVALID_FILENAME;

	if (rc == OK  && fprintf(f,"%d",dot_array.len) < 1)
		rc =  INVALID_INPUT;

	if (rc == OK)
	{
		for (int i = 0; i < dot_array.len && rc == OK; i++)
		{
			fprintf(f, "\n");
			rc = fprintf_dot(f, dot_array.dots[i]);
		}

	}
	return rc;
}






