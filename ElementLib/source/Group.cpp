#include <Group.h>

void Group::addCell(Cell & cell)
{
	this->cells.push_back( &cell );
	cell.addToGroup( *this );
}

std::vector< Cell *> Group::getCells(void)
{
	return this->cells;
}

bool Group::isValid(void) const
{
	bool vality = true;
	unsigned number, count;
	for(number=PossibleValues::firstValue ; number<=PossibleValues::lastValue ; ++number)
	{
		count = 0;
		for( Cell * cell : cells ) if(cell->getValue() == number) count++;
		if(count>1) vality = false;
	}
	return vality;
}
