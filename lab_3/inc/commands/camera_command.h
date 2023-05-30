#ifndef CAMERA_COMMAND_H
#define CAMERA_COMMAND_H

#include "base_command.h"
#include <memory>
#include <cstddef>
#include "camera.h"

template<typename Manager>
class AddCameraCommand : public CameraBaseCommand<Manager>
{
 public:
	AddCameraCommand(shared_ptr<SceneManager> scene_manager, const double x, const double y, const double z)
		: _scene_manager(scene_manager), _x(x), _y(y), _z(z)
	{

	}

	virtual void execute() override
	{
		Dot camera_place(_x, _y, _z);

		std::shared_ptr<Camera> camera(new Camera);

		camera->move(camera_place);

		_scene_manager->get_scene()->add_camera(camera);
		_scene_manager->set_camera(_scene_manager->get_scene()->get_cameras().size() - 1);
	}

 private:
	double _x, _y, _z;
	shared_ptr<SceneManager> _scene_manager;

};

template<typename Manager>
class RemoveCameraCommand : public CameraBaseCommand<Manager>
{
 public:
	RemoveCameraCommand(shared_ptr<SceneManager> scene_manager, const std::size_t& camera_num)
		: _camera_num(camera_num), _scene_manager(scene_manager)
	{

	}

	virtual void execute() override
	{
		_scene_manager->get_scene()->remove_camera(_camera_num);
	}

 private:
	std::size_t _camera_num;
	shared_ptr<SceneManager> _scene_manager;
};

template<typename Manager>
class MoveCameraCommand : public CameraBaseCommand<Manager>
{
 public:
	MoveCameraCommand(shared_ptr<SceneManager> scene_manager,
		shared_ptr<TransformManager> transform_manager,
		const std::size_t& camera_num,
		const double& dx,
		const double& dy) : _dx(dx), _dy(dy), _transform_manager(transform_manager), _scene_manager(scene_manager)
	{

	}

	virtual void execute() override
	{
		//Dot move(_dx, _dy, 0); // TODO::FIX

		auto viewer = _scene_manager->get_scene()->get_cameras().at(_camera_num);

		_transform_manager->move_object(viewer, _dx, _dy, 0);
	}

 private:
	double _dx, _dy;
	std::size_t _camera_num;
	shared_ptr<SceneManager> _scene_manager;
	shared_ptr<TransformManager> _transform_manager;
};

template<typename Manager>
class SetCameraCommand : public CameraBaseCommand<Manager>
{
 public:
	SetCameraCommand(shared_ptr<SceneManager> scene_manager, const std::size_t& camera_num) : _scene_manager(
		scene_manager), _camera_num(camera_num)
	{

	}

	virtual void exec() override
	{
		_scene_manager->set_camera(_camera_num);
	}

 private:
	std::size_t _camera_num;
	shared_ptr<SceneManager> _scene_manager;
};

template<typename Manager>
class RotateCameraCommand : public CameraBaseCommand<Manager>
{
 public:
	RotateCameraCommand(shared_ptr<SceneManager> scene_manager,
		shared_ptr<TransformManager> transform_manager,
		const std::size_t& camera_num,
		const double& dx,
		const double& dy) : _dx(dx), _dy(dy), _transform_manager(transform_manager), _scene_manager(scene_manager)
	{

	}

	virtual void execute() override
	{
		//Dot move(_dx, _dy, 0); // TODO::FIX

		auto viewer = _scene_manager->get_scene()->get_cameras().at(_camera_num);

		_transform_manager->spin_object(viewer, _dx, _dy, 0);
	}

 private:
	double _dx, _dy;
	std::size_t _camera_num;
	shared_ptr<SceneManager> _scene_manager;
	shared_ptr<TransformManager> _transform_manager;
};

template<typename Manager>
class CountCameraCommand : public CameraBaseCommand<Manager>
{
 public:
	CountCameraCommand(shared_ptr<Manager> scene_manager, const std::shared_ptr<size_t>& count) : _scene_manager(
		scene_manager), _count(count)
	{

	}

	void execute() override
	{
		(*_count) = _scene_manager->get_scene()->get_cameras().size();
	}

 private:
	std::shared_ptr<size_t> _count;
	shared_ptr<SceneManager> _scene_manager;
};

#endif
