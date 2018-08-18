#include "stdafx.h"
#include "Grid.h"
#include <iostream>
#include <memory>

void Grid::create_grid()
{
	grid = new Cell*[_size];
	for (size_t i = 0; i < _size; ++i)
	{
		grid[i] = new Cell[_size];
		for (size_t j = 0; j < _size; ++j)
			grid[i][j] = Cell(i, j, (j % 2 == 1 && i % 2 == 1) ? true : false);
	}
}

Grid::Grid(const size_t size) : _size(size)
{
	create_grid();
}

Grid::~Grid()
{
	for (size_t i = 0; i < _size; ++i)
		delete[] grid[i];
	delete grid;
}
