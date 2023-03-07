#include "draw_lines.h"

static dot_t adjust_dot(dot_t &dot,qreal canvas_width, qreal canvas_height)
{
	dot_t adjusted_dot;
	adjusted_dot.x = dot.x + canvas_width / 2;
	adjusted_dot.y = dot.y + canvas_height / 2;
	return adjusted_dot;
}


error_category_t draw_line(line_t &line, dot_array_t &dot_array,QGraphicsScene* canvas)
{
	QPen black_pen(Qt::black);
	black_pen.setWidth(LINE_WIDTH);
	error_category_t rc = OK;
	int from = line.index_from;
	int to = line.index_to;
	if (from  >= 0  && from < dot_array.len  && to  >=  0  && to < dot_array.len) //out of bounds check
	{
		dot_t dot_from = adjust_dot(dot_array.dots[from],canvas->width(),canvas->height());
		dot_t dot_to = adjust_dot(dot_array.dots[to],canvas->width(),canvas->height());
		//dot_t dot_from = dot_array.dots[from];
		//dot_t dot_to = dot_array.dots[to];
		canvas->addLine(dot_from.x,dot_from.y,dot_to.x,dot_to.y,black_pen);
	}
	else
		rc = INVALID_INDEX;
	return rc;
}


error_category_t draw_lines(line_array_t &line_array,dot_array_t &dot_array,QGraphicsScene* canvas)
{
	error_category_t rc = OK;
	for (int i = 0; i < line_array.len && rc == OK; i++)
		rc = draw_line(line_array.lines[i],dot_array,canvas);
	return rc;
}