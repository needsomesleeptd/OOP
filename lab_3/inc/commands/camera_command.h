#ifndef CAMERA_COMMAND_H
#define CAMERA_COMMAND_H

#include "base_command.h"
#include <memory>
#include <cstddef>
#include "camera.h"
#include "scene_manager.h"
#include "transform_manager.h"

class AddCameraCommand : public CameraBaseCommand
{
 public:
	AddCameraCommand(const Dot& position, std::shared_ptr<SceneManager>& scene_manager)
		: _camera_position(position), _scene_manager(scene_manager)
	{

	}
	virtual void execute() override
	{

		std::shared_ptr<Camera> camera(new Camera); // TODO::create factory here
		TransformParams params;
		params.setMoveParams(_camera_position);
		camera->transform(params);

		_scene_manager->get_scene()->add_camera(camera);
		//scene_manager->set_camera(scene_manager->get_scene()->get_cameras().size() - 1);
	}

 private:
	Dot _camera_position;
	std::shared_ptr<SceneManager> _scene_manager;
};

class RemoveCameraCommand : public CameraBaseCommand
{
 public:
	RemoveCameraCommand(std::shared_ptr<SceneManager>& scene_manager, std::size_t camera_id) : _scene_manager(
		scene_manager), _camera_id(camera_id)
	{

	}
	virtual void execute() override
	{
		_scene_manager->get_scene()->remove_camera(_camera_id);
	}

 private:
	std::size_t _camera_id;
	std::shared_ptr<SceneManager> _scene_manager;
};

class TransformCameraCommand : public CameraBaseCommand
{
	using Action = void (Object::*)(std::shared_ptr<Visitor>);
	using Pair = std::pair<std::shared_ptr<Object>, Action>;

 public:
	TransformCameraCommand(std::shared_ptr<SceneManager>& scene_manager,
		size_t camera_id,
		std::shared_ptr<Visitor>& visitor) : _visitor(visitor)
	{
		Action act = &Object::accept;
		auto camera = scene_manager->get_scene()->get_cameras().at(camera_id);
		call = std::make_pair(camera, act);

	};

	void execute() override
	{
		((*call.first).*call.second)(_visitor);
	};

 private:
	Pair call;
	std::shared_ptr<Visitor> &_visitor;

};

class SetCameraCommand : public CameraBaseCommand
{
 public:
	SetCameraCommand(std::shared_ptr<SceneManager>& manager, const std::size_t& camera_num)
		: _camera_num(camera_num), _sceneManager(manager)
	{

	}
	virtual void execute() override
	{
		_sceneManager->set_camera(_camera_num);
	}

 private:
	std::size_t _camera_num;
	std::shared_ptr<SceneManager> _sceneManager;
};

class CountCameraCommand : public CameraBaseCommand
{
	using Action = std::vector<std::shared_ptr<Camera>>(Scene::*)();
	using Pair = std::pair<std::shared_ptr<Scene>, Action>;

 public:
	CountCameraCommand(std::shared_ptr<SceneManager>& manager, std::shared_ptr<size_t>& size)
	{
		_size = size;
		auto scene = manager->get_scene();
		Action act = &Scene::get_cameras;
		call = std::make_pair(scene, act);

	};

	void execute() override
	{
		(*_size) = ((*call.first).*call.second)().size();
	};

 private:
	Pair call;
	std::shared_ptr<Scene> _scene;
	std::shared_ptr<size_t> _size;
};
#endif
