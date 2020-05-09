#pragma once


void generate(int sudoku[9][9]);
void fill_digits(int sudoku[9][9]);
void hide(int sudoku[9][9]);
bool fill_square(int sudoku[9][9], int x, int y);
void swap(int& x, int& y);