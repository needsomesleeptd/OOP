//
// Created by Андрей on 30.05.2023.
//

#include "../../../inc/loader/camera/camera_director.h"
#include "../../../inc/exceptions.h"

CameraDirector::CameraDirector() {
	this->file = std::make_shared<std::ifstream>();
}

CameraDirector::CameraDirector(std::shared_ptr<std::ifstream> &srcFile) {
	file = srcFile;
}

void CameraDirector::open(std::string &fileName) {
	if (!file) {
		std::string msg = "Ошибка при открытии файла.";
		throw SourceException(msg);
	}
	file->open(fileName);
	if (!file) {
		std::string msg = "Ошибка при открытии файла.";
		throw SourceException(msg);
	}
}

void CameraDirector::close() {
	if (!file) {
		std::string msg = "Ошибка при файл не открыт.";
		throw SourceException(msg);
	}
	file->close();
}

std::shared_ptr<Object> CameraDirector::load(std::shared_ptr<BuilderCamera> builder) {
	builder->build();
	double x, y, z;
	*file >> x >> y >> z;
	builder->build_position(x, y, z);
	return builder->get();
}
