//
// Created by Андрей on 23.05.2023.
//

#ifndef INC_3_LAB_LAB_03_3_LAB_MODEL_MODEL_H_
#define INC_3_LAB_LAB_03_3_LAB_MODEL_MODEL_H_

#include "Figure/Figure.h"
#include "BaseModel.h"
#include "Objects/VisiableObject.h"

class Model : public VisiableObject
{
	//friend class DrawCarcassModelAdapter;

 public:
	Model() : _data(new Figure)
	{
	}

	explicit Model(const Figure& otherFigure) :
		_data(otherFigure)
	{
	}
	Model(const Model& model);

	~Model() = default;

	virtual Point getCenter() const;
	virtual void transform(const Matrix<double>& mtr, const Point& center);

 protected:
	Figure _data;

};

#endif //INC_3_LAB_LAB_03_3_LAB_MODEL_MODEL_H_
