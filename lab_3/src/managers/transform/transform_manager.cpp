#include "../../../inc/managers/transform/transform_manager.h"

void TransformManager::move_object(const std::shared_ptr <Object> &object, const double &dx, const double &dy,const double &dz)
{
    Dot move(dx, dy,dz);


    object->move(move);
}

void TransformManager::scale_object(const std::shared_ptr <Object> &object, const double &kx, const double &ky,const double &kz)
{

    Dot scale(kx, ky, kz);


    object->scale(scale);
}

void TransformManager::spin_object(const std::shared_ptr <Object> &object, const double &ox, const double &oy,const double &oz)
{

    Dot rotate(ox, oy, oz);

    object->rotate(rotate);
}

void TransformManager::transform_object(const std::shared_ptr<Object> &object, const Dot &move, const Dot &scale, const Dot &rotate)
{
    object->transform(move, scale, rotate);
}
