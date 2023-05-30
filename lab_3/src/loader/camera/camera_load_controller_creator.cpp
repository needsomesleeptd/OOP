//
// Created by Андрей on 30.05.2023.
//

#include "../../../inc/exceptions.h"
#include "../../../inc/loader/camera/camera_load_controller.h"
#include "../../../inc/loader/camera/camera_load_controller_creator.h"
#include "../../../inc/loader/camera/camera_director.h"

std::shared_ptr<CameraLoadController> CameraLoadControllerCreator::createController() {
	if (nullptr == _controller) {
		makeInstance();
	}

	return _controller;
}

std::shared_ptr<CameraLoadController> CameraLoadControllerCreator::createController(const std::shared_ptr<BaseCameraDirector> &loader) {
	if (nullptr == _controller) {
		makeInstance();
	}
	_controller->setLoader(loader);
	return _controller;
}

void CameraLoadControllerCreator::makeInstance()
{
	static std::shared_ptr<CameraLoadController> controller;
	if (!controller)
	{
		std::shared_ptr<BaseCameraDirector> loader;
		if (name != "")
		{
//			Config cr(this->name);
//			cr.readConfig();
//			if (cr.getLoadSource() == "file")
//				loader = std::shared_ptr<BaseCameraDirector>(new CameraDirector);
//			else
//			{
//				std::string em = "Error : config file";
//				throw SourceException(em);
//			}
			loader = std::shared_ptr<BaseCameraDirector>(new CameraDirector);
		}
		else
		{
			std::string em = "Ошибка в конфиге.";
			throw SourceException(em);
		}
		controller = std::make_shared<CameraLoadController>(loader);
	}

	_controller = controller;
}