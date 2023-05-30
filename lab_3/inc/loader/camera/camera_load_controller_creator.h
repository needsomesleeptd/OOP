//
// Created by Андрей on 30.05.2023.
//

#ifndef INC_3_INC_LOADER_CAMERA_CAMERA_LOAD_CONTROLLER_CREATOR_H_
#define INC_3_INC_LOADER_CAMERA_CAMERA_LOAD_CONTROLLER_CREATOR_H_

#include "camera_load_controller.h"

class CameraLoadControllerCreator
{
 public:
	CameraLoadControllerCreator(std::string fname) : name(fname) {};
	std::shared_ptr<CameraLoadController> createController();
	std::shared_ptr<CameraLoadController> createController(const std::shared_ptr<BaseCameraDirector> &loader);

 private:
	void makeInstance();
	std::shared_ptr<CameraLoadController> _controller;
	std::string name;
};

#endif //INC_3_INC_LOADER_CAMERA_CAMERA_LOAD_CONTROLLER_CREATOR_H_
