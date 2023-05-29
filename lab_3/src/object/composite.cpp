#include "../../inc/object/composite.h"

Composite::Composite(std::shared_ptr<Object> &element)
{
    _elements.push_back(element);
}

Composite::Composite(const std::vector<std::shared_ptr<Object>> &vector)
{
    _elements = vector;
}

bool Composite::add(const std::shared_ptr<Object> &element)
{
    _elements.push_back(element);

    return true;
}

bool Composite::remove(const Iterator &iter)
{
    _elements.erase(iter);

    return true;
}

bool Composite::is_visible()
{
    return false;
}

bool Composite::is_composite() 
{
    return true;
}

void Composite::transform(const Dot &move, const Dot &scale, const Dot &rotate)
{
    for (const auto &element : _elements)
    {
        element->transform(move, scale, rotate);
    }
}

void Composite::rotate(const Dot &rotate_val)
{
	for (const auto &element : _elements)
	{
		element->rotate(rotate_val);
	}
}

void Composite::scale(const Dot &scale_val)
{
	for (const auto &element : _elements)
	{
		element->scale(scale_val);
	}
}

void Composite::move(const Dot &move_val)
{
	for (const auto &element : _elements)
	{
		element->move(move_val);
	}
}

Iterator Composite::begin()
{
    return _elements.begin();
}

Iterator Composite::end()
{
    return _elements.end();
}

void Composite::accept(std::shared_ptr<Visitor> visitor)
{
    for (const auto &element : _elements)
    {
        element->accept(visitor);
    }
}
