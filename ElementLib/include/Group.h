#ifndef GROUP_H
#define GROUP_H

#include <vector>

#include <Cell.h>
#include <SudokuGame.h>

using std::vector;

typedef vector< Cell *> CellVectorPtr;

class Group
{
	public:
		void	addCell(Cell & cell);
		Cell	getCell(const int i);

	private:
		CellVectorPtr cells;
};

#endif
