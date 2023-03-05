//
// Created by Андрей on 02.03.2023.
//

#ifndef INC_1_LAB_ERROR_HANDLING_H
#define INC_1_LAB_ERROR_HANDLING_H

#include <QMessageBox>

enum error_category
{
	OK,
	INVALID_FILENAME,
	INVALID_INPUT,
	IMPOSSIBLE_TO_ALLOCATE
};

typedef error_category error_category_t;

void handle_error(error_category_t error);


#endif //INC_1_LAB_ERROR_HANDLING_H
