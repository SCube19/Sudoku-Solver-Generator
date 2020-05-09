#include"Solver.h"
#include<iostream>
#include<time.h>
#include<cstdlib>
#include<conio.h>
#include<windows.h>

using namespace std;

/////////////////////////////////////////READ SUDOKU/////////////////////

void read_sudoku(int sudoku[9][9])
{
	char input = 0;
	int xPos = 0; //active square coords
	int yPos = 0;

	cout << "Give me a sudoku\n";
	print_sudoku(sudoku, xPos, yPos);


	while (input != 13)
	{
		input = _getch();

		switch (input) //arrow_keys | change active square
		{
		case KEY_RIGHT:
			if (xPos < 8)
				xPos++;
			break;

		case KEY_LEFT:
			if (xPos > 0)
				xPos--;
			break;

		case KEY_UP:
			if (yPos > 0)
				yPos--;
			break;

		case KEY_DOWN:
			if (yPos < 8)
				yPos++;
			break;

		case 8:
			sudoku[yPos][xPos] = 0;
			break;

		default:
			break;
		}
		if (input > 0 && isdigit(input) && possible(sudoku, xPos, yPos, (int)(input - '0'))) //place digit if possible
			sudoku[yPos][xPos] = input - '0';

		system("cls");
		cout << "Give me a sudoku\n";
		print_sudoku(sudoku, xPos, yPos);
	}

	return;
}

/////////////////////////////////////////PRINT SUDOKU///////////////////////

void print_sudoku(int sudoku[9][9], bool inputed[9][9])
{

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (inputed[i][j]) 
				SetConsoleTextAttribute(hConsole, 12);
			else
				SetConsoleTextAttribute(hConsole, 11);

			if (sudoku[i][j] != 0)
				cout << sudoku[i][j];
			else
				cout << ' ';

			if ((j + 1) % 3 == 0)
				SetConsoleTextAttribute(hConsole, 1);
			else
				SetConsoleTextAttribute(hConsole, 15);

			cout << '|';
		}
		if ((i + 1) % 3 == 0)
			SetConsoleTextAttribute(hConsole, 1);
		else
			SetConsoleTextAttribute(hConsole, 15);

		cout << "\n------------------\n";
	}
}

void print_sudoku(int sudoku[9][9], int curX, int curY)
{

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (i == curY && j == curX)
				SetConsoleTextAttribute(hConsole, 40);
			else
				SetConsoleTextAttribute(hConsole, 12);

			if (sudoku[i][j] != 0)
				cout << sudoku[i][j];
			else
				cout << ' ';

			if ((j + 1) % 3 == 0)
				SetConsoleTextAttribute(hConsole, 1);
			else
				SetConsoleTextAttribute(hConsole, 15);

			cout << '|';
		}

		if ((i + 1) % 3 == 0)
			SetConsoleTextAttribute(hConsole, 1);
		else
			SetConsoleTextAttribute(hConsole, 15);

		cout << "\n------------------\n";
	}
}

bool possible(int sudoku[9][9], int x, int y, int value)
{
	for (int i = 0; i < 9; i++)
		if (i != y && sudoku[i][x] == value)
			return false;

	for (int i = 0; i < 9; i++)
		if (i != x && sudoku[y][i] == value)
			return false;

	int startI = 3 * (y / 3);
	int startJ = 3 * (x / 3);

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (startI + i != y && startJ + j != x && sudoku[startI + i][startJ + j] == value)
				return false;

	return true;
}

int solve(int sudoku[9][9], int solution[9][9], int i)
{

	if (i == 81) //last square case
	{
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				solution[i][j] = sudoku[i][j]; //save possible solution
	
		return 1;
	}

	int solutions = 0;
	int x = i % 9; //determine coords from i
	int y = i / 9;

	if (sudoku[y][x] == 0)
	{
		bool anything = false;

		for (int n = 1; n <= 9; n++)
			if (possible(sudoku, x, y, n))
			{
				anything = true; //we found at least one possibility

				sudoku[y][x] = n;
				solutions += solve(sudoku, solution, i + 1); //insert and go ahead
				
				if (solutions > 1000) //limit for calculating non-unique sudokus
					return solutions;
			}
		if (!anything) //we didnt found a solution going this path
			return 0;

		sudoku[y][x] = 0; //reset the square

		return solutions;
	}
	else
	{
		solutions = solve(sudoku, solution, i + 1); 
		if (solutions > 1000)
			return solutions;
	}

}