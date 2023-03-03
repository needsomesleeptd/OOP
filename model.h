#ifndef INC_1_LAB_MODEL_H
#define INC_1_LAB_MODEL_H

#include "dots.h"
#include "lines.h"
#include "dot_math_operations/center.h"
#include "dot_math_operations/rotator.h"
#include "dot_math_operations/scaler.h"

struct model
{
	dot_array_t dots;
	line_array lines;
	dot_t center;
};

typedef model model_t;



#endif //INC_1_LAB_MODEL_H
