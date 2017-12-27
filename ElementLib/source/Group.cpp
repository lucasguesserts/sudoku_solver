#include <Group.h>

void Group::addCell(Cell & cell)
{
	// Add Cell to Group
	this->cells.push_back( &cell );

	// Add the Group to Cell Group list
	cell.addToGroup( *this );
}

Cell Group::getCell(const unsigned i)
{
	return *( this->cells[i] );
}

unsigned Group::getCellValue(const unsigned i)
{
	return this->cells[i]->getValue();
}

unsigned Group::getNumberOfCell(void)
{
	return this->cells.size();
}

CellPtrVector Group::getCells(void)
{
	return this->cells;
}
