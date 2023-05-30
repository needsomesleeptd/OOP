#ifndef MODEL_COMMAND_H
#define MODEL_COMMAND_H

#include <cstddef>
#include <memory>

#include "base_command.h"
#include "object.h"
#include "scene_manager_creator.h"
#include "transform_manager.h"

template<typename Manager>
class LoadModelCommand : public ModelBaseCommand<Manager>
{
	using Action = std::shared_ptr<Object>(Manager::*)(std::string&);
	using Pair = std::pair<std::shared_ptr<Manager>, Action>;

 public:
	LoadModelCommand(std::shared_ptr<Manager>& manager, std::string fileName)
	{
		Action act = &LoadManager::load;
		call = std::make_pair(manager, act);
		_fileName = fileName;
	};

	void execute() override
	{
		auto model = ((*call.first).*call.second)(_fileName);
		CreatorSceneManager().create_manager()->get_scene()->add_model(model);
	};

 private:
	Pair call;
	std::string _fileName;
};

template<typename Manager>
class ScaleModelCommand : public ModelBaseCommand<Manager>
{
	using Action = std::shared_ptr<Object>(Manager::*)(std::string&);
	using Pair = std::pair<std::shared_ptr<Manager>, Action>;

 public:
	ScaleModelCommand(std::shared_ptr<Manager>& manager, int index, double kx, double ky, double kz)
		: _kx(kx), _ky(ky), _kz(kz), _index(index)
	{
		Action act = &TransformManager::scale_object;
		call = std::make_pair(manager, act);

	};

	void execute() override
	{
		std::shared_ptr<Object> model = CreatorSceneManager().create_manager()->get_scene()->get_models().at(_index);
		((*call.first).*call.second)(model, _kx, _ky, _kz);
	};

 private:
	Pair call;
	int _index;
	double _kx, _ky, _kz;
};

template<typename Manager>
class RotateModelCommand : public ModelBaseCommand<Manager>
{
	using Action = std::shared_ptr<Object>(Manager::*)(std::string&);
	using Pair = std::pair<std::shared_ptr<Manager>, Action>;

 public:
	RotateModelCommand(std::shared_ptr<Manager>& manager, int index, double ox, double oy, double oz)
		: _ox(ox), _oy(oy), _oz(oz), _index(index)
	{
		Action act = &TransformManager::spin_object;
		call = std::make_pair(manager, act);

	};

	void execute() override
	{
		std::shared_ptr<Object> model = CreatorSceneManager().create_manager()->get_scene()->get_models().at(_index);
		((*call.first).*call.second)(model, _ox, _oy, _oz);
	};

 private:
	Pair call;
	int _index;
	double _ox, _oy, _oz;
};

template<typename Manager>
class TransformModelCommand : public ModelBaseCommand<Manager>
{
	using Action = std::shared_ptr<Object>(Manager::*)(std::string&);
	using Pair = std::pair<std::shared_ptr<Manager>, Action>;

 public:
	TransformModelCommand(std::shared_ptr<Manager>& manager,
		int index,
		const Dot& move,
		const Dot& scale,
		const Dot& spin) : _rotate(spin), _move(move), _index(index), _scale(scale)
	{
		Action act = &TransformManager::transform_object;
		call = std::make_pair(manager, act);

	};

	void execute() override
	{
		std::shared_ptr<Object> model = CreatorSceneManager().create_manager()->get_scene()->get_models().at(_index);
		((*call.first).*call.second)(model, _move, _scale, _rotate);
	};

 private:
	Pair call;
	int _index;
	Dot _rotate, _move, _scale;
};


template<typename Manager>
class RemoveModelCommand : public ModelBaseCommand<Manager>
{
	using Action = std::shared_ptr<Object>(Manager::*)(std::string&);
	using Pair = std::pair<std::shared_ptr<Manager>, Action>;

 public:
	RemoveModelCommand(std::shared_ptr<Manager>& manager,
		int index) : _index(index)
	{
		Action act = &SceneManager::get_scene()->remove_model;
		call = std::make_pair(manager, act);

	};

	void execute() override
	{
		std::shared_ptr<Object> model = CreatorSceneManager().create_manager()->get_scene()->get_models().at(_index);
		((*call.first).*call.second)(_index);
	};

 private:
	Pair call;
	int _index;
};


template<typename Manager>
class CountModelCommand : public ModelBaseCommand<Manager>
{
	using Action = std::shared_ptr<Object>(Manager::*)(std::string&);
	using Pair = std::pair<std::shared_ptr<Manager>, Action>;

 public:
	CountModelCommand(std::shared_ptr<Manager>& manager)
	{
		Action act = &SceneManager::get_scene()->remove_model;
		call = std::make_pair(manager, act);

	};

	void execute() override
	{
		std::shared_ptr<Object> model = CreatorSceneManager().create_manager()->get_scene()->get_models().at(_index);
		((*call.first).*call.second)(_index);
	};

 private:
	Pair call;
};




class CountModelCommand : public ModelBaseCommand
{
 public:
	CountModelCommand(const std::shared_ptr<size_t>& count);

	virtual void exec() override;

 private:
	std::shared_ptr<size_t> _count;
};

class LoadModelCommand : public ModelBaseCommand
{
 public:
	LoadModelCommand(std::string file_name);

	virtual void exec() override;

 private:
	std::string _file_name;
};

class ExportModelCommand : public ModelBaseCommand
{
 public:
	ExportModelCommand(std::string file_name);

	virtual void exec() override;

 private:
	std::string _file_name;
};

#endif
