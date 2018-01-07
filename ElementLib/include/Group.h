#ifndef GROUP_H
#define GROUP_H

#include <vector>

#include <Cell.h>
#include <PossibleValues.h>

class Group
{
	public:
		void					addCell(Cell & cell);
		std::vector< Cell *>	getCells(void);
		bool					isValid(void) const;

	private:
		std::vector< Cell *>	cells;
};

#endif
