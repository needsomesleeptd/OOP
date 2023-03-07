//
// Created by Андрей on 03.03.2023.
//

#ifndef INC_1_LAB_LINE_H
#define INC_1_LAB_LINE_H
#include "error_handling.h"


struct line
{
	int index_from;
	int index_to;
};

typedef line line_t;

error_category fscanf_line(FILE *f_in, line_t &line);
error_category fprintf_line(FILE *f_out, line_t &line);

#endif //INC_1_LAB_LINE_H
