#pragma once
#include "Cell.h"

class Grid
{
	void create_grid();
protected:
	size_t _size;
	Cell** grid;
public:
	Grid(size_t size);
	~Grid();
};
