//
// Created by Андрей on 23.05.2023.
//

#include "Model.h"


Model::Model(const Model &model)
{
	_data = model._data;
	_id = model._id;
}

Point Model::getCenter() const
{
	return _data.getCenter();
}

void Model::transform(const Matrix<double> &mtr, const Point &center)
{
	_data.transform(mtr, center);
}