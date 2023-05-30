//
// Created by Андрей on 30.05.2023.
//

#ifndef INC_3_INC_LOADER_ABSTRACT_LOAD_CONTROLLER_H_
#define INC_3_INC_LOADER_ABSTRACT_LOAD_CONTROLLER_H_

#include <memory>
#include "base_loader.h"
#include "../object/object.h"


class AbstractLoadController {
 public:
	AbstractLoadController() = default;
	~AbstractLoadController() = default;

	virtual std::shared_ptr<Object> load(std::string &name) = 0;
	virtual void setLoader(std::shared_ptr<BaseLoader> loader) { _loader = loader; };

 protected:
	std::shared_ptr<BaseLoader> _loader;
};


#endif //INC_3_INC_LOADER_ABSTRACT_LOAD_CONTROLLER_H_
