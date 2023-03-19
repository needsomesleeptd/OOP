//
// Created by Андрей on 02.03.2023.
//

#ifndef INC_1_LAB_DOT_H
#define INC_1_LAB_DOT_H

#include "error_handling.h"

struct dot
{
	double x;
	double y;
	double z;
};

typedef dot dot_t;

error_category fscanf_dot(dot_t &dot, FILE *f_in);
error_category fprintf_dot(FILE *f_out,dot_t  &dot);


#endif //INC_1_LAB_DOT_H
