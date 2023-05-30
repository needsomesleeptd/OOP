#include "model_director.h"
#include "exceptions.h"

ModelDirector::ModelDirector() {
	file = std::make_shared<std::ifstream>();
}

ModelDirector::ModelDirector(std::shared_ptr<std::ifstream> &srcFile) {
	file = srcFile;
}

void ModelDirector::open(std::string &fileName) {
	if (!file) {
		std::string msg = "Ошибка. невозможно окрыть файл.";
		throw SourceException(msg);
	}
	file->open(fileName);
	if (!file) {
		std::string msg = "Ошибка. невозможно окрыть файл.";
		throw SourceException(msg);
	}
}

void ModelDirector::close() {
	if (!file) {
		std::string msg = "Ошибка. невозможно файл не открыт.";
		throw SourceException(msg);
	}
	file->close();
}


std::shared_ptr<Object> ModelDirector::load(std::shared_ptr<BuilderModel> builder) {
	builder->build();
	int pointsCount;
	*file >> pointsCount;
	for (int i = 0; i < pointsCount; i++) {
		double x, y, z;
		*file >> x >> y >> z;
		builder->build_dot(x, y, z);
	}

	int edgesCount;
	*file >> edgesCount;
	for (int i = 0; i < edgesCount; i++) {
		int startIndex, endIndex;
		*file >> startIndex >> endIndex;
		builder->build_link(startIndex, endIndex);
	}
	return builder->get();
}
