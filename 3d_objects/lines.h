//
// Created by Андрей on 03.03.2023.
//

#ifndef INC_1_LAB_LINES_H
#define INC_1_LAB_LINES_H

#include "line.h"

struct line_array
{
	int len;
	int cap;
	int step;
	int start_val;
	line_t *lines;
};

typedef line_array line_array_t;

void init_line_dyn_array(line_array &arr);
error_category push_line_back(line_array_t *arr, line_t line);
void clear_line_array(line_array_t &arr);
error_category_t fscanf_lines(FILE *f,line_array_t &lines);
error_category_t fprintf_lines(FILE *f,line_array_t &line_array);



#endif //INC_1_LAB_LINES_H
