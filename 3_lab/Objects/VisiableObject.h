//
// Created by Андрей on 23.05.2023.
//

#ifndef INC_3_LAB_LAB_03_3_LAB_OBJECTS_VISIABLEOBJECT_H_
#define INC_3_LAB_LAB_03_3_LAB_OBJECTS_VISIABLEOBJECT_H_
#include "Entity/Entity.h"

class VisiableObject : Entity
{
 public:
	bool isVisible() override
	{
		return true;
	}
	VisiableObject()  = default;
	~VisiableObject() override = default;

};

#endif //INC_3_LAB_LAB_03_3_LAB_OBJECTS_VISIABLEOBJECT_H_
