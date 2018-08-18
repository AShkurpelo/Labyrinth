#include "stdafx.h"
#include "Cell.h"
#include <typeindex>


Cell::Cell() : _x(0), _y(0), _passable(false) {}


Cell::Cell(const int x, const int y) : _x(x), _y(y), _passable(false) {}

Cell::Cell(const int x, const int y, const bool passable) : _x(x), _y(y), _passable(passable) {}

int Cell::get_x() const
{
	return _x;
}

void Cell::set_x(const int x)
{
	_x = x;
}

int Cell::get_y() const
{
	return _y;
}

void Cell::set_y(const int y)
{
	_y = y;
}

bool Cell::get_passable() const
{
	return _passable;
}

void Cell::set_passable(const bool new_value)
{
	_passable = new_value;
}

bool Cell::operator==(Cell cell) const
{
	return cell.get_x() == _x && cell.get_y() == _y;
}

bool Cell::operator!=(Cell cell) const
{
	return cell.get_x() != _x || cell.get_y() != _y;
}

size_t Cell::operator()(Cell const & x) const noexcept
{
	return (
		(51 + std::hash<int>()(x.get_x())) * 51
		+ std::hash<int>()(x.get_y())
		);
}

Cell::~Cell() {}
