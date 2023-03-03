
#ifndef INC_1_LAB_DOTS_H
#define INC_1_LAB_DOTS_H


#include "dot.h"
#include "error_handling.h"



struct dot_array
{
	int len;
	int cap;
	int step;
	int start_val;
	dot_t *dots;
};

typedef dot_array dot_array_t;

void init_dot_dyn_array(dot_array *arr);
error_category push_dot_back(dot_array_t *arr, dot_t dot);
void clear_dot_array(dot_array_t *arr);




#endif //INC_1_LAB_DOTS_H
