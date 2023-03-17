#include "draw_lines.h"

qreal get_canvas_width(QGraphicsScene* canvas)
{
	return canvas->width();
}

qreal get_canvas_height(QGraphicsScene* canvas)
{
	return canvas->height();
}

static dot_t adjust_dot(dot_t &dot,QGraphicsScene* canvas)
{
	dot_t adjusted_dot;
	adjusted_dot.x = dot.x + get_canvas_width(canvas) / 2;
	adjusted_dot.y = dot.y + get_canvas_height(canvas) / 2;
	return adjusted_dot;
}

error_category_t get_adjusted_dots(dot_array_t &dot_array, dot_array_t &adjusted_dot_array, QGraphicsScene* canvas)
{
	error_category_t rc = OK;
	for (int i = 0;rc == OK && i < dot_array.len;i++)
	{
		dot_t adjusted_dot = adjust_dot(dot_array.dots[i],canvas);
		rc = push_dot_back(adjusted_dot_array,adjusted_dot);
	}
	return rc;
}

void draw_line_dots(dot_t &from, dot_t &to,QGraphicsScene* canvas)
{
	canvas->addLine(from.x,from.y,to.x,to.y);
}

error_category_t draw_line(line_t &line, dot_array_t &adjusted_dot_array,QGraphicsScene* canvas)
{
	if (canvas == NULL)
		return INVALID_CANVAS;
	if (validate_line(line,adjusted_dot_array.len) != OK)
		return INVALID_INDEX;
	if (adjusted_dot_array.len == 0)
		return INVALID_INPUT;


	error_category_t rc = OK;

	int from = line.index_from;
	int to = line.index_to;

	dot_t dot_from = adjusted_dot_array.dots[from];
	dot_t dot_to = adjusted_dot_array.dots[to];
	draw_line_dots(dot_from,dot_to,canvas);


	return rc;
}


error_category_t draw_lines(line_array_t &line_array,dot_array_t &dot_array,QGraphicsScene* canvas)
{
	if (canvas == NULL)
		return INVALID_CANVAS;

	error_category_t rc = OK;
	dot_array_t adjusted_dot_array;
	init_dot_dyn_array(adjusted_dot_array);
	rc = get_adjusted_dots(dot_array,adjusted_dot_array,canvas);

	for (int i = 0; rc == OK && i < line_array.len; i++)
		rc = draw_line(line_array.lines[i],adjusted_dot_array,canvas);

	if (!is_empty(adjusted_dot_array))
		clear_dot_array(adjusted_dot_array);

	return rc;
}