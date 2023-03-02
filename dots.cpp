#include "error_handling.h"
#include "dots.h"




void init_dyn_array(dot_array *arr)
{
	arr->len = 0;
	arr->cap = 0;
	arr->dots = NULL;
	arr->start_val = 2;
	arr->step = 2;
}


error_category push_back(dot_array_t *arr, dot_t dot)
{
	if (arr->dots == NULL)
	{
		void *temp;
		temp = malloc(sizeof(dot_t) * arr->start_val);
		if (!temp)
			return IMPOSSIBLE_TO_ALLOCATE;
		arr->dots = (dot_t*)temp;
		arr->cap = arr->start_val;

	}
	else if (arr->len == arr->cap)
	{
		void *temp;
		temp = realloc(arr->dots,sizeof(dot_t) * arr->cap * arr->step);
		if (!temp)
			return IMPOSSIBLE_TO_ALLOCATE;
		arr->dots = (dot_t*)temp;
		arr->cap *= arr->step;

	}
	arr->dots[arr->len++] = dot;
	return OK;
}

void clear_array(dot_array_t *arr)
{
	free(arr->dots);
	init_dyn_array(arr);
}







