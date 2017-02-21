#include <SudokuGame.h>

SudokuGame::SudokuGame(int s)
{
	allocCells(s);
}

SudokuGame::SudokuGame(void)
{
	allocCells(N_VALUES);
}

Cell SudokuGame::getCell(int x , int y)
{
	return this->cell[x][y];
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
