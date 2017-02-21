#include <SudokuGame.h>

SudokuGame::SudokuGame(int s)
{
	allocCells(s);
	allocLines(s);
	buildCheck(s);
}

Cell SudokuGame::getCell(int x , int y)
{
	return this->cell[x][y];
}

Line SudokuGame::getLine(int l)
{
	return this->line[l];
}

void SudokuGame::allocCells(int s)
{
	// s : game size
	cell.resize( s );
	for(int l=0 ; l<s ; ++l)
	{
		for(int c=0 ; c<s ; ++c)
		{
			Cell newCell(l,c);
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

void SudokuGame::buildCheck(int s)
{
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
}
