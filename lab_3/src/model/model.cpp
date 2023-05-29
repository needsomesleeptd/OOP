#include "../../inc/model/model.h"

Model::Model(const Model &model)
{
    _modelStructure = model._modelStructure;
}

void Model::transform(const Dot &move, const Dot &scale, const Dot &rotate)
{
    _modelStructure->transform(move, scale, rotate);
}

void Model::move(const Dot &move_val)
{
	_modelStructure->move(move_val);
}

void Model::rotate(const Dot &rotate_val)
{
	_modelStructure->rotate(rotate_val);
}

void Model::scale(const Dot &scale_val)
{
	_modelStructure->scale(scale_val);
}



void Model::accept(std::shared_ptr<Visitor> visitor)
{
    visitor->visit(*this);
}
