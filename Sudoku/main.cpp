#include<iostream>
#include<time.h>
#include<cstdlib>
#include<conio.h>
#include<windows.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;

void read_sudoku(int sudoku[9][9]);
void print_sudoku(int sudoku[9][9], bool inputed[9][9]);
void print_sudoku(int sudoku[9][9], int curX, int curY);
bool possible(int sudoku[9][9], int x, int y, int value);
int solve(int sudoku[9][9], int solution[9][9]);

int main()
{
	int sudoku[9][9] = { 0 };
	int solution[9][9] = { 0 };
	read_sudoku(sudoku);

	bool inputed[9][9] = { false };

	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (sudoku[i][j] != 0)
				inputed[i][j] = true;

	system("cls");
	cout << "Solving please wait...";
	system("cls");

	int solutions = solve(sudoku, solution);

	if (solutions > 1)
		cout << "Sudoku is not unique!";
	else if (solutions < 1)
		cout << "Sudoku is unsolvable!";
	else
		print_sudoku(solution, inputed);

	system("pause");
	
	return 0;
}

void read_sudoku(int sudoku[9][9])
{

	char input = 0;
	int xPos = 0;
	int yPos = 0;

	cout << "Give me a sudoku\n";
	print_sudoku(sudoku, xPos, yPos);

	while (input != 13)
	{
		if (true)
		{
			char input = _getch();

			switch (input)
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
			if (input > 0 && isdigit(input) && possible(sudoku, xPos, yPos, (int)(input - '0')))
				sudoku[yPos][xPos] = input - '0';
			if (input == 13)
				return;
			system("cls");
			cout << "Give me a sudoku\n";
			print_sudoku(sudoku, xPos, yPos);
		}
	}
	

}

void print_sudoku(int sudoku[9][9], bool inputed[9][9])
{
	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if(inputed[i][j])
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

int solve(int sudoku[9][9], int solution[9][9])
{
	int solutions = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (sudoku[i][j] == 0)
			{
				for (int n = 1; n <= 9; n++)
					if (possible(sudoku, j, i, n))
					{
						sudoku[i][j] = n;
						solutions += solve(sudoku, solution);

						if (solutions > 1)
							return solutions;
					}
				if (solutions == 0)
					sudoku[i][j] = 0;

				return solutions;
			}
			
		}
	}

	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			solution[i][j] = sudoku[i][j];

	return 1;
}