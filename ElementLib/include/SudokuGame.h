#ifndef SUDOKU_GAME_H
#define SUDOKU_GAME_H

#include <vector>
#include <exception>

#include <Cell.h>
#include <Group.h>
#include <Line.h>

using std::vector;
typedef vector< vector<Cell> > CellMatrix;
typedef vector<Line> LineVector;

class SudokuGame{
	public:

		explicit SudokuGame(int s = N_VALUES);

		Cell getCell(int x , int y);
		Line getLine(int l);

	private:

		CellMatrix cell;
		LineVector line;

		void allocCells(int s);
		void allocLines(int s);
		void buildCheck(int s);
};

#endif
