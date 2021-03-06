#include "stdafx.h"
#include "Labyrinth.h"
#include <random>
#include <unordered_set>
#include <unordered_map>
#include <ctime>

void Labyrinth::create()
{
	srand(time(NULL));

	make_first_line();
	for (size_t i = 3; i < _size; i += 2)
	{
		std::vector<Cell> block = {};
		for (size_t j = 1; j < _size; j += 2)
		{
			const bool go_rigth_rnd = rand() % 2;
			if (go_rigth_rnd)
				go_rigth(block, i, j);
			else
				go_up(block, i, j);
		}
	}

	choose_start_finish();
}

void Labyrinth::go_rigth(std::vector<Cell> &block, size_t i, size_t j)
{
	if (j != _size - 2)
	{
		grid[i][j + 1].set_passable(true);
		block.push_back(grid[i][j]);
	}
	else
	{
		go_up(block, i, j);
	}
}

void Labyrinth::go_up(std::vector<Cell> &block, size_t i, size_t j)
{
	block.push_back(grid[i][j]);
	Cell up_from = block[rand() % block.size()];
	grid[up_from.get_x() - 1][up_from.get_y()].set_passable(true);
	block.clear();
}

void Labyrinth::make_first_line()
{
	for (size_t j = 2; j < _size - 1; j += 2)
		grid[1][j].set_passable(true);
}

void Labyrinth::choose_start_finish()
{
	size_t y = rand() % (_size - 2) + 1;
	start_cell = Cell(0, y);
	grid[0][y].set_passable(true);

	while (true)
	{
		y = rand() % (_size - 2) + 1;
		if (grid[_size - 2][y].get_passable())
		{
			finish_cell = Cell(_size - 1, y);
			grid[_size - 1][y].set_passable(true);
			break;
		}
	}
}

std::vector<std::unordered_set<Cell, Cell>> Labyrinth::get_solutions()
{
	std::vector<std::unordered_set<Cell, Cell>> solutions;
	std::unordered_map<Cell, Cell, Cell> came_from;
	std::unordered_set<Cell, Cell> visited;

	DFS(start_cell, came_from, solutions, visited);

	return solutions;
}

void Labyrinth::DFS(Cell cell, std::unordered_map<Cell, Cell, Cell>& came_from,
	std::vector<std::unordered_set<Cell, Cell>>& solutions, std::unordered_set<Cell, Cell>& visited)
{
	if (cell == finish_cell)
	{
		solutions.push_back(restore_path(came_from));
		return;
	}

	visited.insert(cell);

	if (grid[cell.get_x() + 1][cell.get_y()].get_passable() && visited.find(grid[cell.get_x() + 1][cell.get_y()]) == visited.end())
	{
		came_from[grid[cell.get_x() + 1][cell.get_y()]] = cell;
		DFS(grid[cell.get_x() + 1][cell.get_y()], came_from, solutions, visited);
	}
	if (cell == start_cell)
		return;
	if (grid[cell.get_x() - 1][cell.get_y()].get_passable() && visited.find(grid[cell.get_x() - 1][cell.get_y()]) == visited.end())
	{
		came_from[grid[cell.get_x() - 1][cell.get_y()]] = cell;
		DFS(grid[cell.get_x() - 1][cell.get_y()], came_from, solutions, visited);
	}
	if (grid[cell.get_x()][cell.get_y() + 1].get_passable() && visited.find(grid[cell.get_x()][cell.get_y() + 1]) == visited.end())
	{
		came_from[grid[cell.get_x()][cell.get_y() + 1]] = cell;
		DFS(grid[cell.get_x()][cell.get_y() + 1], came_from, solutions, visited);
	}
	if (grid[cell.get_x()][cell.get_y() - 1].get_passable() && visited.find(grid[cell.get_x()][cell.get_y() - 1]) == visited.end())
	{
		came_from[grid[cell.get_x()][cell.get_y() - 1]] = cell;
		DFS(grid[cell.get_x()][cell.get_y() - 1], came_from, solutions, visited);
	}

	visited.erase(cell);
}

std::unordered_set<Cell, Cell> Labyrinth::restore_path(std::unordered_map<Cell, Cell, Cell>& came_from)
{
	std::unordered_set<Cell, Cell> path = { finish_cell };
	Cell cur = finish_cell;
	do
	{
		cur = came_from[cur];
		path.insert(cur);
	} while (cur != start_cell);

	return path;
}

Labyrinth::Labyrinth(size_t size) : Grid(size)
{
	create();
}


Labyrinth::~Labyrinth()
{
}

void Labyrinth::print(std::ostream& output_target) const
{
	for (size_t i = 0; i < _size; ++i)
	{
		for (size_t j = 0; j < _size; ++j)
			output_target << (grid[i][j].get_passable() ? "   " : "MVV");
		output_target << std::endl;
	}
	output_target << std::endl;
}

void Labyrinth::print_solved(std::ostream& output_target)
{
	auto solutions = get_solutions();

	for (size_t i = 0; i < _size; ++i)
	{
		for (size_t j = 0; j < _size; ++j)
		{
			bool in_solution = false;
			for (auto solution : solutions)
			{
				if (solution.find(grid[i][j]) != solution.end())
					in_solution = true;
			}

			if (in_solution)
				output_target << " * ";
			else
				output_target << (grid[i][j].get_passable() ? "   " : "MVV");
		}
		output_target << std::endl;
	}
	output_target << std::endl;
}

void Labyrinth::print_image(char* const png_file_name)
{
	FILE *f;
	unsigned char *img = nullptr;
	const int filesize = 54 + 3 * 2 * int(_size);  //w is your image width, h is image height, both int
	if (img)
		free(img);
	img = static_cast<unsigned char *>(malloc(3 * 2 * int(_size)));
	memset(img, 0, sizeof(img));

	for (int i = 0; i<_size; i++)
	{
		for (int j = 0; j<_size; j++)
		{
			int x = i; int y = (_size - 1) - j;
			int r = static_cast<double>(i) / _size * 255;
			int g = static_cast<double>(j) / _size * 255;
			int b = i + j;
			if (r > 255) r = 255;
			if (g > 255) g = 255;
			if (b > 255) b = 255;
			img[(x + y*_size) * 3 + 2] = static_cast<unsigned char>(r);
			img[(x + y*_size) * 3 + 1] = static_cast<unsigned char>(g);
			img[(x + y*_size) * 3 + 0] = static_cast<unsigned char>(b);
		}
	}

	unsigned char bmpfileheader[14] = { 'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0 };
	unsigned char bmpinfoheader[40] = { 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0 };
	unsigned char bmppad[3] = { 0,0,0 };

	bmpfileheader[2] = static_cast<unsigned char>(filesize);
	bmpfileheader[3] = static_cast<unsigned char>(filesize >> 8);
	bmpfileheader[4] = static_cast<unsigned char>(filesize >> 16);
	bmpfileheader[5] = static_cast<unsigned char>(filesize >> 24);

	bmpinfoheader[4] = static_cast<unsigned char>(_size);
	bmpinfoheader[5] = static_cast<unsigned char>(_size >> 8);
	bmpinfoheader[6] = static_cast<unsigned char>(_size >> 16);
	bmpinfoheader[7] = static_cast<unsigned char>(_size >> 24);
	bmpinfoheader[8] = static_cast<unsigned char>(_size);
	bmpinfoheader[9] = static_cast<unsigned char>(_size >> 8);
	bmpinfoheader[10] = static_cast<unsigned char>(_size >> 16);
	bmpinfoheader[11] = static_cast<unsigned char>(_size >> 24);

	fopen_s(&f, png_file_name, "wb");
	fwrite(bmpfileheader, 1, 14, f);
	fwrite(bmpinfoheader, 1, 40, f);
	for (int i = 0; i<_size; i++)
	{
		fwrite(img + (_size*(_size - i - 1) * 3), 3, _size, f);
		fwrite(bmppad, 1, (4 - (_size * 3) % 4) % 4, f);
	}
	fclose(f);
}
