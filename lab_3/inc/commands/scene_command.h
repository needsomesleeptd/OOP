#ifndef SCENE_COMMAND_H
#define SCENE_COMMAND_H

#include <memory>
#include "base_command.h"
#include "abstract_drawer.h"
#include "draw_manager_creator.h"
#include "scene_manager_creator.h"
#include "load_scene_controller_creator.h"
#include "load_manager.h"

class DrawSceneCommand : public SceneBaseCommand
{
	using Action = void (Composite::*)(std::shared_ptr<Visitor>);
	using Pair = std::pair<std::shared_ptr<Composite>, Action>;

 public:
	DrawSceneCommand(std::shared_ptr<SceneManager>& sceneManager,
		std::shared_ptr<DrawManager>& drawManager,
		std::shared_ptr<AbstractDrawer> drawer)
	{
		Action act = &Composite::accept;
		_camera = sceneManager->get_camera();
		auto models = sceneManager->get_scene()->get_composite();
		call = std::make_pair(models, act);
		_drawer = drawer;
		_drawManager = drawManager;
	};

	void execute() override
	{
		_drawer->clear_scene();
		_drawManager->set_drawer(_drawer);
		_drawManager->set_camera(_camera);
		((*call.first).*call.second)(_drawManager);
	};
 private:
	std::shared_ptr<AbstractDrawer> _drawer;
	Pair call;
	std::shared_ptr<SceneManager> _sceneManager;
	std::shared_ptr<DrawManager> _drawManager;
	std::shared_ptr<Camera> _camera;
};

class LoadSceneCommand : public SceneBaseCommand
{
	using Action = std::shared_ptr<Object>(LoadManager::*)(std::string&);
	using Pair = std::pair<std::shared_ptr<LoadManager>, Action>;
 public:
	LoadSceneCommand(std::shared_ptr<SceneManager> scene_manager,
		std::shared_ptr<LoadManager> load_manager,
		std::string file_name)
	{
		Action action = &LoadManager::load;
		call = std::make_pair(load_manager, action);
	}

	virtual void execute()
	{
		auto moderator = LoadSceneControllerCreator().create_controller();
		_load_manager->set_loader(moderator);
		((*call.first).*call.second)(_file_name);
	}

 private:
	std::string _file_name;
	std::shared_ptr<SceneManager> _scene_manager;
	std::shared_ptr<LoadManager> _load_manager;
	Pair call;

};

/*template<typename SceneManager>
class ExportSceneCommand : public SceneBaseCommand<SceneManager>
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
