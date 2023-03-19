#ifndef INC_1_LAB_MODEL_H
#define INC_1_LAB_MODEL_H

#include <QGraphicsScene>


#include "3d_objects/dots.h"
#include "3d_objects/lines.h"

#include "dot_math_operations/center_movement.h"
#include "dot_math_operations/rotator.h"
#include "dot_math_operations/scaler.h"

#include "drawing/draw_lines.h"

#include "error_handling.h"


struct model
{
	dot_array_t dots;
	line_array lines;
	dot_t center;
};

typedef model model_t;


model_t init_model();
error_category_t fscanf_model(model_t &model,FILE *f_in);
error_category_t rotate_model(model_t &model, rotator_t &rotator);
error_category_t scale_model(model_t &model, scaler_t &scaler);
error_category_t draw_model(model_t &model, QGraphicsScene *canvas);
void calculate_center_model(model_t &model);
error_category_t move_model(model_t &model, dot_t &vector);
error_category_t fprintf_model(model_t &model, FILE *f_out);
void clear_model(model_t &model);
error_category_t validate_model(model_t &model);
error_category_t save_model(model_t &model,const char* filename);
error_category_t load_model(model_t &model,const char* filename);
error_category_t change_center(model_t &model, dot_t &dot);





#endif //INC_1_LAB_MODEL_H
