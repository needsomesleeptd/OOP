//
// Created by Андрей on 30.05.2023.
//

#ifndef INC_3_INC_LOADER_CAMERA_BASE_CAMERA_DIRECTOR_H_
#define INC_3_INC_LOADER_CAMERA_BASE_CAMERA_DIRECTOR_H_


#include <memory>
#include "../../builder/builder_camera.h"
#include "../base_loader.h"

class BaseCameraDirector: public BaseLoader {
 public:
	virtual std::shared_ptr<Object> load(std::shared_ptr<BuilderCamera> builder) = 0;
};



#endif //INC_3_INC_LOADER_CAMERA_BASE_CAMERA_DIRECTOR_H_
