#include <Group.h>

void Group::addCell(Cell & cell)
{
	this->cells.push_back( &cell );
}

Cell Group::getCell(const int i)
{
	return *( this->cells[i] );
}

int Group::getNumberOfCell(void)
{
	return this->cells.size();
}
