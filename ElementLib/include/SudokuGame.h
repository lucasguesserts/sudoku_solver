#ifndef SUDOKU_GAME_H
#define SUDOKU_GAME_H

#include <vector>
#include <exception>

#include <PossibleValues.h>
#include <Cell.h>
#include <Group.h>
#include <Row.h>
#include <Column.h>
#include <Rectangle.h>

#include <hdf5.h>

class SudokuGame{
	public:
		SudokuGame(void);

		// Cell functionalities
		unsigned				getCellValue(unsigned row , unsigned column) const;
		unsigned				getCellNumberOfPossibleValues(unsigned row , unsigned column) const;
		unsigned				getCellUniquePossibleValue(unsigned row , unsigned column) const;
		void					setCellValue(unsigned row , unsigned column , unsigned value);
		std::vector<Group *>	getCellGroups(unsigned row , unsigned column);

		// solvers
		bool					isValid(void) const;
		bool					isSolved(void) const;
		void					solveForOnePossibleValue(void);
		
		// IO
		void					set(const std::vector< std::vector<unsigned> > data);
		void					createFile(const char * const fileName, const char * datasetName) const;
		void					appendInFile(const char * const fileName, const char * datasetName) const;
		void					readFromFile(const char * const fileName, const char * datasetName);

		static const unsigned	size;

	private:
		std::vector< std::vector<Cell> >		cell;
		std::vector<Row>						row;
		std::vector<Column>						column;
		std::vector <std::vector<Rectangle> >	rectangle;

		void allocCells(void);
		void allocRows(void);
		void allocColumns(void);
		void allocRectangles(void);
		void buildCheck(void);
};

bool operator==(SudokuGame lhs , SudokuGame rhs);

#endif
