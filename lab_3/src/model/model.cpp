#include "../../inc/model/model.h"

Model::Model(const Model &model)
{
    _modelStructure = model._modelStructure;
}

void Model::transform(const Mover &move, const Scaler &scale, const Rotator &rotate)
{
    _modelStructure->transform(move, scale, rotate);
}

void Model::accept(std::shared_ptr<Visitor> visitor)
{
    visitor->visit(*this);
}
