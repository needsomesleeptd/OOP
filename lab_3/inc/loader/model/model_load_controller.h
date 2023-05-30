#ifndef LAB_03_MODELLOADCONTROLLER_H
#define LAB_03_MODELLOADCONTROLLER_H

#include "base_model_director.h"
#include "abstract_load_controller.h"



class ModelLoadController: public AbstractLoadController {
public:
	explicit ModelLoadController(std::shared_ptr<BaseModelDirector> loader);
	~ModelLoadController() = default;

	std::shared_ptr<Object> load(std::string &fileName) override;

private:
	std::shared_ptr<BuilderModel> _builder;
	std::shared_ptr<BaseModelDirector> _loader;
};


#endif //LAB_03_MODELLOADCONTROLLER_H
