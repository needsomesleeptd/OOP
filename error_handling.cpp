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
		case INVALID_SCALER:
			QMessageBox::warning(NULL,"Ошибка изменения размеров модели","Была попытка умножить точку на нулевой вектор");
			break;
		case MODEL_NOT_INITIALIZED:
			QMessageBox::warning(NULL,"Модель не была инициализированна","Невозможно выполнить действие - модель не была инициализированна");
			break;
		case INVALID_INDEX:
			QMessageBox::warning(NULL,"Одна из линий не валидна","Одна из линий имеет связь с несуществующей точкой");
			break;
		case INVALID_CANVAS:
			QMessageBox::warning(NULL,"Канвас не валиден","Канваса по которому поступил запрос на рисование не существует");
			break;





	}
}