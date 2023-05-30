#ifndef LAB_03_MODELDIRECTOR_H
#define LAB_03_MODELDIRECTOR_H

#include "base_model_director.h"

class ModelDirector: public BaseModelLoader {
public:
	ModelDirector();
	explicit ModelDirector(std::shared_ptr<std::ifstream> &srcFile);
	~ModelDirector() override = default;

	void open(std::string &fileName) override;
	void close() override;
	std::shared_ptr<Object> load(std::shared_ptr<BuilderModel> builder) override;

protected:
	std::shared_ptr<std::ifstream> file;
};

#endif //LAB_03_MODELDIRECTOR_H
