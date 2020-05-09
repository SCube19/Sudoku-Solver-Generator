#include"Generator.h"
#include"Solver.h"
#include<time.h>
#include<cstdlib>
#include<array>
#include<iostream>

using namespace std;

void generate(int sudoku[9][9])
{
	srand(time(NULL));
	fill_digits(sudoku);
	hide(sudoku);
}

void fill_digits(int sudoku[9][9])
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
		{
			if (!fill_square(sudoku, j, i))
				j = -1;
		}
}

bool fill_square(int sudoku[9][9], int x, int y)
{
	int digits[] = { 1,2,3,4,5,6,7,8,9 };
	int q = 8, index;

	while (q >= 0)
	{
		index = rand() % (q + 1);

		if (possible(sudoku, x, y, digits[index]))
		{
			sudoku[y][x] = digits[index];
			return true;
		}

		swap(digits[index], digits[q]);
		q--;
	}
	return false;
}

void hide(int sudoku[9][9])
{

}

void swap(int& x, int& y)
{
	int tmp = x;
	x = y;
	y = tmp;
}