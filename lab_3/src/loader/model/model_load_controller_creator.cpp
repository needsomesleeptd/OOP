#include "model_load_controller_creator.h"
#include "model_director.h"
#include "configuration.h"
#include "exceptions.h"
#include "model_load_controller.h"

std::shared_ptr<ModelLoadController> ModelLoadControllerCreator::createController() {
	if (_controller == nullptr) {
		makeInstance();
	}
	return _controller;
}

std::shared_ptr<ModelLoadController> ModelLoadControllerCreator::createController(const std::shared_ptr<BaseModelDirector> &loader) {
	if (_controller == nullptr) {
		makeInstance();
	}
	_controller->setLoader(loader);
	return _controller;
}

void ModelLoadControllerCreator::makeInstance() {
	static std::shared_ptr<ModelLoadController> controller;
	if (!controller) {
		std::shared_ptr<BaseModelDirector> loader;
		if (name != "") {
//			GraphLibConfig cr (this->name);
//			cr.readConfig();
//			if (cr.getLoadSource() == "file")
//				loader = std::shared_ptr<BaseModelDirector>(new ModelDirector);
//			else
//			{
//				string em = "Error : config file";
//				throw FileError(em);
//			}
			loader = std::shared_ptr<BaseModelDirector>(new ModelDirector);
		}
		else {
			std::string msg = "Некорректный конфиг.";
			throw SourceException(msg);
		}
		controller = std::make_shared<ModelLoadController>(loader);
	}

	_controller = controller;
}
