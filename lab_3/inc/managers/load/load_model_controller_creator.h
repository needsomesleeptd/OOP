#ifndef LOAD_MODEL_CONTROLLER_CREATOR_H
#define LOAD_MODEL_CONTROLLER_CREATOR_H

#include "load_model_controller.h"

class LoadModelControllerCreator
{
 public:
	LoadModelControllerCreator() = default;
	explicit LoadModelControllerCreator(const std::string& path_to_config)
		: _path_to_config(std::make_shared<std::string>(path_to_config))
	{
	};
	std::shared_ptr<LoadModelController> create_controller();
	std::shared_ptr<LoadModelController> create_controller(const std::shared_ptr<BaseLoaderModel>& loader);

 private:
	void create_instance();

	std::shared_ptr<LoadModelController> _controller;
	std::shared_ptr<std::string> _path_to_config;
};

#endif
