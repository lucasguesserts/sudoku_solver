#ifndef SUDOKU_GAME_H
#define SUDOKU_GAME_H

#include <vector>
#include <exception>

#include <Cell.h>
#include <Group.h>
#include <Line.h>
#include <Column.h>
#include <Rectangle.h>

using std::vector;
typedef vector< vector<Cell> >			CellMatrix;
typedef vector<Line>					LineVector;
typedef vector<Column>					ColumnVector;
typedef vector< vector <Rectangle> >	RectangleMatrix;

class SudokuGame{
	public:

		explicit SudokuGame(int s = N_VALUES);

		Cell	getCell(int x , int y);
		Line	getLine(int l);
		Column	getColumn(int l);

	private:

		CellMatrix		cell;
		LineVector		line;
		ColumnVector	column;
		RectangleMatrix	rectangle;

		void allocCells(int s);
		void allocLines(int s);
		void allocColumns(int s);
		void allocRectangles(void);
		void buildCheck(int s);
};

#endif
