#include "model_load_controller.h"
#include "exceptions.h"

ModelLoadController::ModelLoadController(std::shared_ptr<BaseModelLoader> loader): _builder(new ModelBuilder) {
	_loader = loader;
}

std::shared_ptr<BaseObject> ModelLoadController::load(std::string &fileName) {
	try {
		_loader->open(fileName);
	}
	catch (SourceException &error) {
		std::string msg = "Ошибка. Невозможно открыть файл.";
		throw SourceException(msg);
	}

	std::shared_ptr<BaseObject> model;
	try {
		model = _loader->load(_builder);
	}
	catch (std::exception &error) {
		std::string msg = "Ошибка при чтении модели из файла.";
		throw SourceException(msg);
	}

	_loader->close();
	return model;
}
