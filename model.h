#ifndef INC_1_LAB_MODEL_H
#define INC_1_LAB_MODEL_H

#include <QGraphicsScene>


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


model_t init_model();
error_category_t fscanf_model(FILE *f_in,model_t &model);
void center_model(model_t &model);
void rotate_model(model_t &model, rotator_t &rotator);
void scale_model(model_t &model, scaler_t &scaler);
void draw_model(model_t &model, QGraphicsScene &canvas);


#endif //INC_1_LAB_MODEL_H
