//
// Created by Андрей on 01.06.2023.
//
#include "TransformVisitor.h"

void TransformVisitor::visit(Model& model)
{

	model.transform(_transform_params);
}
void TransformVisitor::visit(Camera& viewer)
{
	viewer.transform(_transform_params);
}
void TransformVisitor::visit(Composite& composite)
{

}

void TransformVisitor::set_params(TransformParams transform_params)
{
	_transform_params = transform_params;
}