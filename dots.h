
#ifndef INC_1_LAB_DOTS_H
#define INC_1_LAB_DOTS_H


#include "dot.h"



struct dot_array
{
	int len;
	int cap;
	int step;
	int start_val;
	dot_t *dots;
};

typedef dot_array dot_array_t;





#endif //INC_1_LAB_DOTS_H
