#ifndef GROUP_H
#define GROUP_H

#include <vector>

#include <Cell.h>

using std::vector;

typedef vector< Cell *> CellPtrVector;

class Group
{
	public:
		void	addCell(Cell & cell);
		Cell	getCell(const int i);
		int		getNumberOfCell(void);

	private:
		CellPtrVector cells;
};

#endif
