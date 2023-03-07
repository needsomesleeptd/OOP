#include "error_handling.h"

void handle_error(error_category_t error)
{
	switch (error)
	{
		case INVALID_FILENAME:
			QMessageBox::warning(NULL,"Ошибка в имени файла","Невозсожно открыть данный файл(проверьте выделенные права)");
			break;
		case INVALID_INPUT:
			QMessageBox::warning(NULL,"Ошибка в содержании файла","Введенный файл имеет невалидный формат");
			break;
		case IMPOSSIBLE_TO_ALLOCATE:
			QMessageBox::warning(NULL,"Ошибка выделения памяти","Введенный файл слишком большой, невозможно выделить достаточный объем памяти под его данные");
			break;
		case INVALID_REQUEST:
			QMessageBox::warning(NULL,"Ошибка выполнения запроса","Над моделью была попытка произвести невалидные действия");
			break;

	}
}