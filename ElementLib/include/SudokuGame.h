#ifndef SUDOKU_GAME_H
#define SUDOKU_GAME_H

#include <vector>

#include <Cell.h>

using std::vector;
typedef vector< vector<Cell> > CellMatrix;

class SudokuGame{
	public:

		explicit SudokuGame(int s);
		SudokuGame(void);

		Cell getCell(int x , int y);

	private:

		CellMatrix cell;

		void allocCells(int s);
};

#endif
