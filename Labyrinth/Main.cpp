// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Labyrinth.h"


int main()
{
	Labyrinth labyrinth(11);

	labyrinth.print();
	labyrinth.print_solved();

	std::system("pause");
	return 0;
}

