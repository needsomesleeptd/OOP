//
// Created by Андрей on 30.05.2023.
//

#ifndef INC_3_INC_LOADER_CAMERA_CAMERA_DIRECTOR_H_
#define INC_3_INC_LOADER_CAMERA_CAMERA_DIRECTOR_H_


#include "../../../inc/exceptions.h"


#include "base_camera_director.h"

class CameraDirector: public BaseCameraDirector {
 public:
	CameraDirector();
	explicit CameraDirector(std::shared_ptr<std::ifstream> &srcFile);
	~CameraDirector() override = default;

	void open(std::string &fileName) override;
	void close() override;

	std::shared_ptr<Object> load(std::shared_ptr<BuilderCamera> builder) override;

 protected:
	std::shared_ptr<std::ifstream> file;
};


#endif //INC_3_INC_LOADER_CAMERA_CAMERA_DIRECTOR_H_
