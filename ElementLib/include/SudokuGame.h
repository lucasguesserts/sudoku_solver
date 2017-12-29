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
		explicit SudokuGame();
		~SudokuGame(void);

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
		void		createFile(const char * fileName);
		void		openFile(const char * fileName);
		void		closeFile(void);
		void		writeProblem();
		void 		readProblem();
		void 		writeSolution();
		void 		readSolution();

	private:
		CellMatrix		cell;
		RowVector		row;
		ColumnVector	column;
		RectangleMatrix	rectangle;

		hid_t			file;
		bool			isFileOpen;

		void write(const char * datasetName);
		void read(const char * datasetName);

		void allocCells(unsigned s);
		void allocRows(unsigned s);
		void allocColumns(unsigned s);
		void allocRectangles(void);
		void buildCheck(unsigned s);
};

bool operator==(SudokuGame lhs , SudokuGame rhs);

#endif
