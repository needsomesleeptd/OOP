#ifndef INC_1_LAB_ERROR_HANDLING_H
#define INC_1_LAB_ERROR_HANDLING_H

#include <QMessageBox>
#define EPS 1e-7

enum error_category
{
	OK,
	INVALID_FILENAME,
	INVALID_INPUT,
	IMPOSSIBLE_TO_ALLOCATE,
	INVALID_REQUEST,
	INVALID_INDEX,
	INVALID_COMMAND,
	INVALID_SCALER,
	MODEL_NOT_INITIALIZED,
	IMPOSSIBLE_TO_OUTPUT
};

typedef error_category error_category_t;

void handle_error(error_category_t error);


#endif //INC_1_LAB_ERROR_HANDLING_H
