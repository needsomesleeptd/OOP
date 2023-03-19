//
// Created by Андрей on 07.03.2023.
//

#ifndef INC_1_LAB_DRAW_LINES_H
#define INC_1_LAB_DRAW_LINES_H


#include <QGraphicsScene>

#include "3d_objects/dots.h"
#include "3d_objects/lines.h"

#define LINE_WIDTH 6

error_category_t draw_lines(line_array_t &line_array,dot_array_t &dot_array,QGraphicsScene* canvas);
dot_t adjust_dot(dot_t &dot,QGraphicsScene* canvas);



#endif //INC_1_LAB_DRAW_LINES_H
