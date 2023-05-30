#include "load_manager.h"
#include "load_scene_controller_creator.h"
#include "load/load_model_controller.h"

LoadManager::LoadManager()
{
    _loader = LoadSceneControllerCreator().create_controller();
}

std::shared_ptr<Object> LoadManager::load(std::string &name)
{
    return _loader->load(name);
}

void LoadManager::set_loader(std::shared_ptr<AbstractLoadController> loader)
{
    _loader = loader;
}
