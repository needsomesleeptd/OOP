#include "transform_manager.h"

void TransformManager::move_object(const std::shared_ptr <Object> &object, const double &dx, const double &dy,const double &dz)
{
	Dot move(dx, dy,dz);
	Dot scale(1, 1, 1);
	Dot rotate(0, 0, 0);
	TransformParams params(move, scale, rotate);
	object->transform(params);
}

void TransformManager::scale_object(const std::shared_ptr <Object> &object, const double &kx, const double &ky,const double &kz)
{
	Dot move(0, 0,0);
	Dot scale(kx, ky, kz);
	Dot rotate(0, 0, 0);
	TransformParams params(move, scale, rotate);
	object->transform(params);
}

void TransformManager::spin_object(const std::shared_ptr <Object> &object, const double &ox, const double &oy,const double &oz)
{
	Dot move(0, 0,0);
	Dot scale(1, 1, 1);
	Dot rotate(ox, oy, oz);
	TransformParams params(move, scale, rotate);
	object->transform(params);
}

void TransformManager::transform_object(const std::shared_ptr<Object> &object, const Dot &move, const Dot &scale, const Dot &rotate)
{
	TransformParams params(move, scale, rotate);
    object->transform(params);
}
