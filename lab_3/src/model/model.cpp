#include "../../inc/model/model.h"
#include "transform.h"
Model::Model(const Model &model)
{
    _modelStructure = model._modelStructure;
}

void Model::transform(const TransformParams& transform_params)
{
    _modelStructure->transform(transform_params.getMoveParams(), transform_params.getScaleParams(),transform_params.getRotateParams());
}

void Model::accept(std::shared_ptr<Visitor> visitor)
{
    visitor->visit(*this);
}
