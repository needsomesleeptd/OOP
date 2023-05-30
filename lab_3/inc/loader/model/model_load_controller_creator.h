#ifndef LAB_03_MODELLOADCONTROLLERCREATOR_H
#define LAB_03_MODELLOADCONTROLLERCREATOR_H

#include "model_load_controller.h"

class ModelLoadControllerCreator {
public:
	ModelLoadControllerCreator(std::string fileName): name(fileName) {};
	std::shared_ptr<ModelLoadController> createController();
	std::shared_ptr<ModelLoadController> createController(const std::shared_ptr<BaseModelLoader> &loader);

private:
	void makeInstance();
	std::shared_ptr<ModelLoadController> _controller;
	std::string name;
};


#endif //LAB_03_MODELLOADCONTROLLERCREATOR_H
