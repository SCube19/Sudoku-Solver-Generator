#include<iostream>
#include<windows.h>
#include<conio.h>
#include"Solver.h"
#include"Generator.h"

using namespace std;


int main()
{
	int sudoku[9][9] = { 0 };

	int k;
	cout << "Do you want to solve or generate?" << endl;
	cout << "1. Solve  2. Generate";
	k = _getch();

	if (k == '1')
	{
		int solution[9][9] = { 0 };
		read_sudoku(sudoku);

		bool inputed[9][9] = { false };

		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				if (sudoku[i][j] != 0)
					inputed[i][j] = true;

		system("cls");
		cout << "Solving please wait...";

		int solutions = solve(sudoku, solution, 0);

		system("cls");
		if (solutions < 1)
			cout << "Sudoku is unsolvable!" << endl << endl;
		else
		{
			if (solutions > 1)
			{
				cout << "Sudoku is not unique!" << endl;
				if (solutions <= 1000)
					cout << solutions << " possible solutions!" << endl;
				else
					cout << "More than 1000 solutions. Are you sure you didnt enter empty board?" << endl;

				cout << "Printing one of the possibilities:" << endl << endl;
			}

			print_sudoku(solution, inputed);
		}
	}
	else
	{
		system("cls");
		cout << "Generating, please wait...";

		generate(sudoku);

		bool inputed[9][9] = { false };
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				if (sudoku[i][j] != 0)
					inputed[i][j] = true;

		system("cls");
		print_sudoku(sudoku, inputed);
	}
	system("pause");
	
	return 0;
}

