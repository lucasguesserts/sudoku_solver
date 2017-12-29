#ifndef SUDOKU_GAME_H
#define SUDOKU_GAME_H

#include <Foreach.h>

#include <vector>
#include <exception>

#include <Cell.h>
#include <Group.h>
#include <Row.h>
#include <Column.h>
#include <Rectangle.h>

#include <hdf5.h>

using std::vector;
typedef vector< vector<Cell> >			CellMatrix;
typedef vector<Row>						RowVector;
typedef vector<Column>					ColumnVector;
typedef vector< vector <Rectangle> >	RectangleMatrix;

class SudokuGame{
	public:
		explicit SudokuGame(unsigned s = N_VALUES);

		// Cell functionalities
		Cell		getCell(unsigned r , unsigned c);
		void		setCellValue(unsigned r , unsigned c , unsigned value);
		unsigned	getCellValue(unsigned r , unsigned c) const;
		unsigned	getCellNumberOfPossibleValues(unsigned r , unsigned c) const;
		unsigned	getCellUniquePossibleValue(unsigned r , unsigned c) const;

		// Group functionalities
		GroupPtrVector	getCellGroups(unsigned r , unsigned c) const;
		Row			getRow(unsigned r);
		Column		getColumn(unsigned c);
		Rectangle	getRectangle(unsigned r , unsigned c);

		// solvers
		bool		isValid(void);
		void		solverForOnePossibleValue(void);
		
		// IO
		void		set(const unsigned * const dataArray);
		void		set(const vector<unsigned> data);
		void		set(const vector< vector<unsigned> > data);
		void		write(const char * const fileName);
		void		read(const char * const fileName);

	private:
		CellMatrix		cell;
		RowVector		row;
		ColumnVector	column;
		RectangleMatrix	rectangle;

		void allocCells(unsigned s);
		void allocRows(unsigned s);
		void allocColumns(unsigned s);
		void allocRectangles(void);
		void buildCheck(unsigned s);
};

bool operator==(SudokuGame lhs , SudokuGame rhs);

#endif
