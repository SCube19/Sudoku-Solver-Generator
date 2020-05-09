#pragma once

constexpr auto KEY_UP = 72;
constexpr auto KEY_DOWN = 80;
constexpr auto KEY_LEFT = 75;
constexpr auto KEY_RIGHT = 77;

void read_sudoku(int sudoku[9][9]); //sudoku input 
void print_sudoku(int sudoku[9][9], bool inputed[9][9]); //sudoku print after solve
void print_sudoku(int sudoku[9][9], int curX, int curY); //sudoku print during inputing
bool possible(int sudoku[9][9], int x, int y, int value); //check if digit placement is possible at (x,y)
int solve(int sudoku[9][9], int solution[9][9], int i); //solve sudoku 