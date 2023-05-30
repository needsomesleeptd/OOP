//
// Created by Андрей on 30.05.2023.
//

#ifndef INC_3_INC_LOADER_BASE_LOADER_H_
#define INC_3_INC_LOADER_BASE_LOADER_H_


#include <string>
#include <fstream>

class BaseLoader {
 public:
	BaseLoader() = default;
	virtual ~BaseLoader() = default;

	virtual void open(std::string &fileName) = 0;
	virtual void close() = 0;
};


#endif //INC_3_INC_LOADER_BASE_LOADER_H_
