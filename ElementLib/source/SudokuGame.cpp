#include <SudokuGame.h>

SudokuGame::SudokuGame(int s)
{
	allocCells(s);
	allocLines(s);
	allocColumns(s);
	allocRectangles();

	buildCheck(s);
}

Cell SudokuGame::getCell(int l , int c)
{
	return this->cell[l][c];
}

int SudokuGame::getCellNumberOfPossibleValues(int l , int c) const
{
	return this->cell[l][c].getNumberOfPossibleValues();
}

Line SudokuGame::getLine(int l)
{
	return this->line[l];
}

Column SudokuGame::getColumn(int c)
{
	return this->column[c];
}

Rectangle SudokuGame::getRectangle(int l , int c)
{
	return this->rectangle[l][c];
}

void SudokuGame::allocCells(int s)
{
	// s : game size
	cell.resize( s );
	for(int l=0 ; l<s ; ++l)
	{
		for(int c=0 ; c<s ; ++c)
		{
			// x : column
			// y : line
			Cell newCell(c,l);
			this->cell[l].push_back( newCell );
		}
	}
}

void SudokuGame::allocLines(int s)
{
	// Resize the 'line' vector to have size 's'.
	// For each line 'l', add all line 'l' cells.
	// To add all line 'l' cells, it is necessary to
	// add the cell of each column 'c'.
	this->line.resize( s );
	for(int l=0 ; l<s ; ++l)
	{
		for(int c=0 ; c<s ; ++c){
			this->line[l].addCell( this->cell[l][c] );
		}
	}
}

void SudokuGame::allocColumns(int s)
{
	// Resize the 'column' vector to have size 's'.
	// For each column 'c', add all column 'c' cells.
	// To add all column 'c' cells, it is necessary to
	// add the cell of each line 'l'.
	this->column.resize( s );
	for(int c=0 ; c<s ; ++c)
	{
		for(int l=0 ; l<s ; ++l){
			this->column[c].addCell( this->cell[l][c] );
		}
	}
}

void SudokuGame::allocRectangles(void)
{
	// l: rectangle number of lines
	// c: rectangle number of columns
	// s: game size
	int defaultSize = 3;

	// resize lines and columns
	this->rectangle.resize(defaultSize);
	for(int c=0 ; c<defaultSize ; ++c)
	{
		this->rectangle[c].resize(defaultSize);
	}

	// add Cells to each Rectangle
	for(int l=0 ; l<defaultSize ; ++l)
	{
		for(int c=0 ; c<defaultSize ; ++c)
		{
			for(int cl=0 ; cl<defaultSize ; ++cl) // cl: Cell Line
			{
				for(int cc=0 ; cc<defaultSize ; ++cc) // cc: Cell Column
				{
					this->rectangle[l][c].addCell( this->cell[cl + defaultSize * l][cc + defaultSize * c] );
				}
			}
		}
	}
}

//// ############### solvers ###############
//void SudokuGame::solverForOnePossibleValue(void)
//{
//	bool changed;
//	do
//	{
//		for( int l=0 ; l<N_VALUES ; ++l )
//		{
//			for( int c=0 ; c<N_VALUES ; ++c )
//			{
//				PossibleValues pv = this->getCell(l,c).getPossibleValues();
//				if( pv.size() == 1 )
//				{

//				}
//			}
//		}
//	}while( changed==true );
//}

void SudokuGame::buildCheck(int s)
{
	// default size for a Rectangle
	int defaultSize = 3;

	// Check CellMatrix line number
	if ( this->cell.size() != s ) throw "CellMatrix line numbers wrong";

	// Check CellMatrix column number
	for( int l=0 ; l<s ; ++l)
	{
		if ( this->cell[l].size() != s ) throw "CellMatrix column number wrong";
	}

	// Check LineVector size
	if ( this->line.size() != s ) throw "LineVector size wrong";

	// Check each LineVector size
	for( int l=0 ; l<s ; ++l)
	{
		if ( this->line[l].getNumberOfCell() != s ) throw "Number of cells in line vector wrong";
	}

	// Check ColumnVector size
	if ( this->column.size() != s ) throw "ColumnVector size wrong";

	// Check each ColumnVector size
	for( int c=0 ; c<s ; ++c)
	{
		if ( this->column[c].getNumberOfCell() != s ) throw "Number of cells in column vector wrong";
	}

	// Check RectangleMatrix line number
	if ( this->rectangle.size() != defaultSize ) throw "Number of lines in RectangleMatrix wrong";

	// Check each RectangleMatrix column number
	for(int l=0 ; l<defaultSize ; ++l)
	{
		if ( this->rectangle[l].size() != defaultSize ) throw "Number of columns in RectangleMatrix wrong";
	}
}
