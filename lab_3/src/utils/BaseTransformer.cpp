//
// Created by Андрей on 29.05.2023.
//
#include "../../inc/utils/BaseTransformer.h"
BaseTransformer::BaseTransformer(const double x, const double y, const double z)
{
	set_x(x);
	set_y(y);
	set_z(z);
}

BaseTransformer::BaseTransformer(const BaseTransformer &&BaseTransformer) noexcept
{
	set_x(BaseTransformer._x);
	set_y(BaseTransformer._y);
	set_z(BaseTransformer._z);

	BaseTransformer.~BaseTransformer();
}

BaseTransformer &BaseTransformer::operator = (BaseTransformer &&BaseTransformer) noexcept
{
	set_x(BaseTransformer._x);
	set_y(BaseTransformer._y);
	set_z(BaseTransformer._z);

	BaseTransformer.~BaseTransformer();

	return *this;
}

double BaseTransformer::get_x() const
{
	return _x;
}

double BaseTransformer::get_y() const
{
	return _y;
}

double BaseTransformer::get_z() const
{
	return _z;
}

void BaseTransformer::set_x(const double &x)
{
	_x = x;
}

void BaseTransformer::set_y(const double &y)
{
	_y = y;
}

void BaseTransformer::set_z(const double &z)
{
	_z = z;
}

bool BaseTransformer::operator == (const BaseTransformer &BaseTransformer) const noexcept
{
	return (BaseTransformer._x == _x) && (BaseTransformer._y == _y) && (BaseTransformer._z == _z);
}

bool BaseTransformer::is_equal(const BaseTransformer &BaseTransformer) const noexcept
{
	return *this == BaseTransformer;
}

bool BaseTransformer::operator != (const BaseTransformer &BaseTransformer) const noexcept
{
	return !(*this == BaseTransformer);
}

bool BaseTransformer::is_not_equal(const BaseTransformer &BaseTransformer) const noexcept {
	return !(*this == BaseTransformer);
}

BaseTransformer BaseTransformer::operator + (const BaseTransformer &BaseTransformer)
{
	class BaseTransformer d{ *this};

	d.set_x(d._x + BaseTransformer._x);
	d.set_y(d._y + BaseTransformer._y);
	d.set_z(d._z + BaseTransformer._z);

	return d;
}

BaseTransformer BaseTransformer::operator - (const BaseTransformer &BaseTransformer)
{
	class BaseTransformer d{ *this};

	d.set_x(d._x - BaseTransformer._x);
	d.set_y(d._y - BaseTransformer._y);
	d.set_z(d._z - BaseTransformer._z);

	return d;
}

void BaseTransformer::move(const double dx, const double dy, const double dz)
{
	set_x(_x + dx);
	set_y(_y + dy);
	set_z(_y + dz);
}

void BaseTransformer::scale(const double kx, const double ky, const double kz)
{
	set_x(_x * kx);
	set_y(_y * ky);
	set_z(_z * kz);
}