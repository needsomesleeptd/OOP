//
// Created by Андрей on 23.05.2023.
//

#ifndef INC_3_LAB_LAB_03_3_LAB_ENTITY_ENTITY_H_
#define INC_3_LAB_LAB_03_3_LAB_ENTITY_ENTITY_H_

#include <vector>

#include "Point.h"

#include <memory>


class Entity;
using Iterator = std::vector<std::shared_ptr<Entity>>::iterator;


class Entity
{
 public:
	Entity()
	{
		_id = _nextId++;

	};
	virtual ~Entity() = default;

	virtual bool add(const std::shared_ptr<Entity> &) { return false; };
	virtual bool remove(const Iterator &) { return false; };
	virtual void updateCenter() {};

	virtual bool isVisible() { return false; };
	virtual bool isComposite() { return  false; };

	virtual Point getCenter() const = 0;
	virtual void moveElemsToOrigin(const Point &) { }
	virtual void moveElemsToCenter(const Point &) { }
	virtual void transformElems(const Matrix<double> &) { }
	virtual void transform(const Matrix<double> &mtr, const Point &center) = 0;

	virtual Iterator begin() { return Iterator(); };
	virtual Iterator end() { return Iterator(); };

	virtual std::size_t getId() { return _id; }
 protected:
	std::size_t _id;
	static std::size_t _nextId;

	Point _center;
};

#endif //INC_3_LAB_LAB_03_3_LAB_ENTITY_ENTITY_H_
