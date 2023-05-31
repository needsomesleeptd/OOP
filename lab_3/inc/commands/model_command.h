#ifndef MODEL_COMMAND_H
#define MODEL_COMMAND_H

#include <cstddef>
#include <memory>

#include "base_command.h"
#include "object.h"

#include "scene_manager_creator.h"
#include "transform_manager.h"
#include "scene.h"
#include "transform.h"
#include "scene_manager.h"
#include "load_manager.h"

class LoadModelCommand : public ModelBaseCommand
{
	using Action = std::shared_ptr<Object>(LoadManager::*)(std::string&);
	using Pair = std::pair<std::shared_ptr<LoadManager>, Action>;

 public:
	LoadModelCommand(std::shared_ptr<LoadManager>& manager, std::string fileName, std::shared_ptr<Scene>& scene)
	{
		Action act = &LoadManager::load;
		call = std::make_pair(manager, act);
		_fileName = fileName;
		_scene = scene;
	};

	void execute() override
	{
		_scene->add_model(((*call.first).*call.second)(_fileName));
	};

 private:
	Pair call;
	std::string _fileName;
	std::shared_ptr<Scene> _scene;
};

class TransformModelCommand : public ModelBaseCommand
{
	using Action = void (Object::*)(std::shared_ptr<Visitor>);
	using Pair = std::pair<std::shared_ptr<Object>, Action>;

 public:
	TransformModelCommand(std::shared_ptr<SceneManager>& scene_manager,
		size_t model_id,
		std::shared_ptr<Visitor>& visitor) : _visitor(visitor)
	{
		Action act = &Object::accept;
		auto Model = scene_manager->get_scene()->get_models().at(model_id);
		call = std::make_pair(Model, act);

	};

	void execute() override
	{
		((*call.first).*call.second)(_visitor);
	};

 private:
	Pair call;
	std::shared_ptr<Visitor> _visitor;

};



class AddModelCommand: public ModelBaseCommand {
	using Action = void(Scene::*)(const std::shared_ptr<Object>&);
	using Pair = std::pair<std::shared_ptr<Scene>, Action>;

 public:
	AddModelCommand(std::shared_ptr<SceneManager> &manager,std::shared_ptr<Object> model) {
		auto scene = manager->get_scene();
		Action act = &Scene::add_model;
		call = std::make_pair(scene, act);
		_model = model
	};

	void execute() override {
		((*call.first).*call.second)(_model);
	};

 private:
	Pair call;
	std::shared_ptr<Object> _model;
	std::shared_ptr<Scene> _scene;
};


class RemoveModelCommand: public ModelBaseCommand {
	using Action = void(Scene::*)(const std::size_t);
	using Pair = std::pair<std::shared_ptr<Scene>, Action>;

 public:
	RemoveModelCommand(std::shared_ptr<SceneManager> &manager, int modelIndex) {
		auto scene = manager->get_scene();
		Action act = &Scene::remove_model;
		call = std::make_pair(scene, act);
		_modelIndex = modelIndex;
	};

	void execute() override {
		((*call.first).*call.second)(_modelIndex);
	};

 private:
	Pair call;
	std::size_t _modelIndex;
	std::shared_ptr<Scene> _scene;
};

class CountModelCommand : public ModelBaseCommand
{
	using Action = std::vector<std::shared_ptr<Object>>(Scene::*)();
	using Pair = std::pair<std::shared_ptr<Scene>, Action>;

 public:
	CountModelCommand(std::shared_ptr<SceneManager>& manager, std::shared_ptr<size_t>& size)
	{
		_size = size;
		auto scene = manager->get_scene();
		Action act = &Scene::get_models;
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

#endif //LAB_03_MODELCOMMAND_H
