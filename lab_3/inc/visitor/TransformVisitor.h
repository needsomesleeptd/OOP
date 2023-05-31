//
// Created by Андрей on 01.06.2023.
//

#ifndef INC_3_INC_VISITOR_TRANSFORMVISITOR_H_
#define INC_3_INC_VISITOR_TRANSFORMVISITOR_H_

#include "visitor.h"
#include "transform.h"
#include "model.h"
#include "camera.h"
#include "composite.h"

class Model;
class Camera;
class Composite;

class TransformVisitor : Visitor
{
 public:
	TransformVisitor() = default;
	~TransformVisitor() = default;

	virtual void visit(Model& model) override;
	virtual void visit(Camera& viewer) override;
	virtual void visit(Composite& composite) override;
 private:
	TransformParams transform_params;

};
#endif //INC_3_INC_VISITOR_TRANSFORMVISITOR_H_
