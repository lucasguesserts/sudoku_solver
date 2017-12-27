#ifndef SUDOKU_GAME_H
#define SUDOKU_GAME_H

#include <vector>
#include <exception>

#include <Cell.h>
#include <Group.h>
#include <Line.h>
#include <Column.h>
#include <Rectangle.h>

#include <hdf5.h>

using std::vector;
typedef vector< vector<Cell> >			CellMatrix;
typedef vector<Line>					LineVector;
typedef vector<Column>					ColumnVector;
typedef vector< vector <Rectangle> >	RectangleMatrix;

class SudokuGame{
	public:

		explicit SudokuGame(unsigned s = N_VALUES);

		// Cell functionalities
		Cell		getCell(unsigned l , unsigned c);
		void		setCellValue(unsigned l , unsigned c , unsigned value);
		unsigned	getCellValue(unsigned l , unsigned c) const;
		unsigned	getCellNumberOfPossibleValues(unsigned l , unsigned c) const;
		unsigned	getCellUniquePossibleValue(unsigned l , unsigned c) const;

		// Group functionalities
		Line		getLine(unsigned l);
		Column		getColumn(unsigned l);
		Rectangle	getRectangle(unsigned l , unsigned c);

		// solvers
		//void		solverForOnePossibleValue(void);
		
		// IO
		void		setUsingArray(unsigned dataArray[9][9]);
		void		write(const char * const fileName);
		void		read(const char * const fileName);

	private:

		CellMatrix		cell;
		LineVector		line;
		ColumnVector	column;
		RectangleMatrix	rectangle;

		void allocCells(unsigned s);
		void allocLines(unsigned s);
		void allocColumns(unsigned s);
		void allocRectangles(void);
		void buildCheck(unsigned s);
};

#endif
