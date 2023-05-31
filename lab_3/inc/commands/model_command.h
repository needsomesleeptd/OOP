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



class LoadModelCommand: public ModelBaseCommand {
	using Action = std::shared_ptr<Object>(LoadManager::*)(std::string&);
	using Pair = std::pair<std::shared_ptr<LoadManager>, Action>;

 public:
	LoadModelCommand(std::shared_ptr<LoadManager> &manager, std::string fileName, std::shared_ptr<Scene> &scene) {
		Action act = &LoadManager::load;
		call = std::make_pair(manager, act);
		_fileName = fileName;
		_scene = scene;
	};

	void execute() override {
		_scene->add_model(((*call.first).*call.second)(_fileName));
	};

 private:
	Pair call;
	std::string _fileName;
	std::shared_ptr<Scene> _scene;
};


class TransformModelCommand: public ModelBaseCommand {
	using Action = void(Object::*)(std::shared_ptr<Visitor>);
	using Pair = std::pair<std::shared_ptr<Object>, Action>;

 public:
	TransformModelCommand(std::shared_ptr<TransformManager> &manager, std::shared_ptr<Object> &model, const TransformParams &params) {
		Action act = &Object::accept;
		call = std::make_pair(model, act);
		_transformParams = params;
		_transformManager = manager;
	};

	void execute() override {
		_transformManager->set_params(_transformParams);
		((*call.first).*call.second)(_transformManager);
	};

 private:
	Pair call;
	TransformParams _transformParams;
	std::shared_ptr<TransformManager> _transformManager;
};

class MoveModelCommand: public ModelBaseCommand {
 public:
	MoveModelCommand(const double &dx, const double &dy, const double &dz, const std::size_t modelIndex);
	void execute() override;

 private:
	std::size_t _modelIndex;
	double _dx, _dy, _dz;
};


class ScaleModelCommand: public ModelBaseCommand {
 public:
	ScaleModelCommand(const double &kx, const double &ky, const double &kz, const std::size_t modelIndex);
	void execute() override;

 private:
	std::size_t _modelIndex;
	double _kx, _ky, _kz;
};


class RotateModelCommand: public ModelBaseCommand {
 public:
	RotateModelCommand(const double &ox, const double &oy, const double &oz, const std::size_t modelIndex);
	void execute() override;

 private:
	std::size_t _modelIndex;
	double _ox, _oy, _oz;
};

class AddModelCommand: public ModelBaseCommand {
 public:
	AddModelCommand(std::shared_ptr<BaseObject> model);
	void execute() override;

 private:
	std::shared_ptr<BaseObject> _model;
};


template <typename Manager>
class RemoveModelCommand: public BaseModelCommand<Manager> {
	using Action = void(Scene::*)(const std::size_t);
	using Pair = std::pair<std::shared_ptr<Scene>, Action>;

 public:
	RemoveModelCommand(std::shared_ptr<SceneManager> &manager, int modelIndex) {
		auto scene = manager->getScene();
		Action act = &Scene::removeModel;
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

template <typename Manager>
class CountModelCommand: public BaseModelCommand<Manager> {
	using Action = std::vector<std::shared_ptr<BaseObject>>(Scene::*)();
	using Pair = std::pair<std::shared_ptr<Scene>, Action>;

 public:
	CountModelCommand(std::shared_ptr<SceneManager> &manager, std::shared_ptr<size_t> &size) {
		_size = size;
		auto scene = manager->getScene();
		Action act = &Scene::getModels;
		call = std::make_pair(scene, act);

	};

	void execute() override {
		(*_size) = ((*call.first).*call.second)().size();
	};

 private:
	Pair call;
	std::shared_ptr<Scene> _scene;
	std::shared_ptr<size_t> _size;
};

#endif //LAB_03_MODELCOMMAND_H
