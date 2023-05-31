#ifndef CAMERA_COMMAND_H
#define CAMERA_COMMAND_H

#include "base_command.h"
#include <memory>
#include <cstddef>
#include "camera.h"
#include "scene_manager.h"

class AddCameraCommand : public CameraBaseCommand
{
 public:
	AddCameraCommand(SceneManager& sceneManager, const double x, const double y, const double z);
	virtual void execute() override;

 private:
	double _x, _y, _z;
	SceneManager _sceneManager;
};

class RemoveCameraCommand : public CameraBaseCommand
{
 public:
	RemoveCameraCommand(const std::size_t& cameraIndex);
	virtual void execute() override;

 private:
	std::size_t _cameraIndex;
};

class MoveCameraCommand : public CameraBaseCommand
{
 public:
	MoveCameraCommand(const std::size_t& cameraIndex, const double& dx, const double& dy);
	virtual void execute() override;

 private:
	double _dx, _dy;
	std::size_t _cameraIndex;
};

class SetCameraCommand : public CameraBaseCommand
{
 public:
	SetCameraCommand(const std::size_t& cameraIndex);
	virtual void execute() override;

 private:
	std::size_t _cameraIndex;
};

class CountCameraCommand : public CameraBaseCommand
{
 public:
	CountCameraCommand(const std::shared_ptr<size_t>& count);
	virtual void execute() override;

 private:
	std::shared_ptr<size_t> _count;
};

AddCameraCommand::AddCameraCommand(SceneManager& sceneManager, const double x, const double y, const double z)
	: _x(x), _y(y), _z(z)
{
}

void AddCameraCommand::execute()
{
	Dot cameraPosition(_x, _y, _z);
	std::shared_ptr<Camera> camera(new Camera);
	camera->move_camera(cameraPosition);
	_sceneManager->getScene()->addCamera(camera);
	_sceneManager->setCamera(_sceneManager->getScene()->getCameras().size() - 1);
};

RemoveCameraCommand::RemoveCameraCommand(const size_t& cameraIndex)
	: _cameraIndex(cameraIndex)
{
}

void RemoveCameraCommand::execute()
{
	SceneManagerCreator().createManager()->getScene()->removeCamera(_cameraIndex);
}

MoveCameraCommand::MoveCameraCommand(const size_t& cameraIndex, const double& dx, const double& dy)
	: _dx(dx), _dy(dy), _cameraIndex(cameraIndex)
{
}

void MoveCameraCommand::execute()
{
	auto camera = SceneManagerCreator().createManager()->getScene()->getCameras().at(_cameraIndex);
	TransformManagerCreator().createManager()->move_object(camera, _dx, _dy, 0);
}

SetCameraCommand::SetCameraCommand(const size_t& cameraIndex)
	: _cameraIndex(cameraIndex)
{
}

void SetCameraCommand::execute()
{
	SceneManagerCreator().createManager()->setCamera(_cameraIndex);
}

CountCameraCommand::CountCameraCommand(const std::shared_ptr<size_t>& count)
	: _count(count)
{
}

void CountCameraCommand::execute()
{
	(*_count) = SceneManagerCreator().createManager()->getScene()->getCameras().size();
}

#endif
