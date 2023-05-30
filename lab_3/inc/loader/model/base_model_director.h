#ifndef LAB_03_BASEMODELDIRECTOR_H
#define LAB_03_BASEMODELDIRECTOR_H

#include "../base_loader.h"
#include "../../builder/builder_model.h"

class BaseModelLoader: public BaseLoader {
public:
	virtual std::shared_ptr<Object> load(std::shared_ptr<BuilderModel> builder) = 0;
};


#endif //LAB_03_BASEMODELDIRECTOR_H
