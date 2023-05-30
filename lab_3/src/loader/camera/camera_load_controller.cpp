//
// Created by Андрей on 30.05.2023.
//

#include "../../../inc/loader/camera/camera_load_controller.h"
#include "../../../inc/exceptions.h"

CameraLoadController::CameraLoadController(std::shared_ptr<BaseCameraDirector> loader) {
	_loader = loader;
	_builder = std::make_shared<BuilderCamera>();
}

std::shared_ptr<Object> CameraLoadController::load(std::string &file_name) {
	try {
		_loader->open(file_name);
	}
	catch (SourceException &error) {
		std::string msg = "Ошибка при открытии файла.";
		throw SourceException(msg);
	}

	std::shared_ptr<Object> camera;
	try {
		camera = _loader->load(_builder);
	}
	catch (std::exception &error) {
		std::string msg = "Ошибка при чтении модели.";
		throw SourceException(msg);
	}

	_loader->close();
	return camera;
}
