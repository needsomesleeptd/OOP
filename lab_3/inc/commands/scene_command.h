#ifndef SCENE_COMMAND_H
#define SCENE_COMMAND_H

#include <memory>
#include "base_command.h"
#include "abstract_drawer.h"
#include "draw_manager_creator.h"
#include "scene_manager_creator.h"
#include "load_scene_controller_creator.h"

template<typename Manager>
class DrawSceneCommand : public SceneBaseCommand<Manager>
{
	using Action = std::shared_ptr<Object>(Manager::*)(std::string&);
	using Pair = std::pair<std::shared_ptr<Manager>, Action>;
 public:
	DrawSceneCommand(std::shared_ptr<Manager>& scene_manager,
		std::shared_ptr<DrawManager>& draw_manager,
		std::shared_ptr<AbstractDrawer> drawer)
		: _drawer(drawer), _scene_manager(scene_manager), _draw_manager(draw_manager)
	{
		Action act = &SceneManager::get_scene()->get_composite()->accept;
		call = std::make_pair(scene_manager, act);

	}

	void execute() override
	{
		auto camera = _scene_manager->get_camera();

		_drawer->clear_scene();
		_draw_manager->set_drawer(_drawer);
		_draw_manager->set_camera(camera);
		_scene_manager->get_scene()->get_composite()->accept(_draw_manager);
		((*call.first).*call.second)(_draw_manager);
	}

 private:
	std::shared_ptr<AbstractDrawer> _drawer;
	Pair call;
	std::shared_ptr<SceneManager> _scene_manager;
	std::shared_ptr<DrawManager> _draw_manager;

};

template<typename Manager>
class LoadSceneCommand : public SceneBaseCommand<Manager>
{
	using Action = std::shared_ptr<Object>(Manager::*)(std::string&);
	using Pair = std::pair<std::shared_ptr<Manager>, Action>;
 public:
	LoadSceneCommand(std::shared_ptr<Manager> scene_manager,
		std::shared_ptr<LoadManager> load_manager,
		std::string file_name)
	{
		Action act = &SceneManager::set_scene;
		call = std::make_pair(scene_manager, act);
	}

	virtual void execute()
	{
		auto moderator = LoadSceneControllerCreator().create_controller();
		_load_manager->set_loader(moderator);
		auto scene = std::dynamic_pointer_cast<Scene>(_load_manager->load(_file_name));

		((*call.first).*call.second)(scene);
	}

 private:
	std::string _file_name;
	std::shared_ptr<SceneManager> _scene_manager;
	std::shared_ptr<LoadManager> _load_manager;
	Pair call;


};

/*template<typename Manager>
class ExportSceneCommand : public SceneBaseCommand<Manager>
{
 public:
	ExportSceneCommand(std::string file_name);

	virtual void execute() override;

 private:
	std::string _file_name;
};*/

/*class SetDrawerCommand : public SceneBaseCommand
{
 public:
	ExportSceneCommand(DrawManager
	&manager,
	DrawManager::set_drawer& func, std::shared_ptr<AbstractDrawer>
	drawer);

	virtual void execute() override;

 private:
	AbstractDrawer _drawer;
};*/

#endif
