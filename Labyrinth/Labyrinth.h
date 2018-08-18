#pragma once
#include "Grid.h"
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

class Labyrinth : Grid
{
	Cell start_cell, finish_cell;

	void create();
	void go_rigth(std::vector<Cell> &block, size_t i, size_t j);
	void go_up(std::vector<Cell> &block, size_t i, size_t j);
	void make_first_line();
	void choose_start_finish();

	std::vector<std::unordered_set<Cell, Cell>> get_solutions();
	void DFS(Cell cell, std::unordered_map<Cell, Cell, Cell>& came_from, std::vector<std::unordered_set<Cell, Cell>>& solutions,
		std::unordered_set<Cell, Cell>& visited);
	std::unordered_set<Cell, Cell> restore_path(std::unordered_map<Cell, Cell, Cell>& came_from);
public:
	Labyrinth(size_t size);
	~Labyrinth();

	void print(std::ostream& output_target = std::cout) const;
	void print_solved(std::ostream& output_target = std::cout);
	void print_image(char* const file_name);
};

