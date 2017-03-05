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

		// Cell functionalities
		Cell		getCell(int l , int c);
		void		setCellValue(int l , int c , int value);
		int			getCellNumberOfPossibleValues(int l , int c) const;
		unsigned	getCellUniquePossibleValue(int l , int c) const;

		// Group functionalities
		Line		getLine(int l);
		Column		getColumn(int l);
		Rectangle	getRectangle(int l , int c);

		// solvers
		//void		solverForOnePossibleValue(void);

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
