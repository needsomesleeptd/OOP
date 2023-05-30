//
// Created by Андрей on 30.05.2023.
//

#ifndef INC_3_INC_LOADER_CAMERA_CAMERA_LOAD_CONTROLLER_H_
#define INC_3_INC_LOADER_CAMERA_CAMERA_LOAD_CONTROLLER_H_


#include "base_camera_director.h"
#include "abstract_load_controller.h"

class CameraLoadController: public AbstractLoadController {
 public:
	explicit CameraLoadController(std::shared_ptr<BaseCameraDirector> loader);
	~CameraLoadController() = default;

	std::shared_ptr<Object> load(std::string &fileName) override;

 private:
	std::shared_ptr<BuilderCamera> _builder;
	std::shared_ptr<BaseCameraDirector> _loader;
};

#endif //INC_3_INC_LOADER_CAMERA_CAMERA_LOAD_CONTROLLER_H_
