//
// Created by Андрей on 01.06.2023.
//
#include "TransformVisitor.h"

void TransformVisitor::visit(Model& model)
{

	model.transform(transform_params);
}
void TransformVisitor::visit(Camera& viewer)
{
	viewer.transform(transform_params);
}
void TransformVisitor::visit(Composite& composite)
{

}