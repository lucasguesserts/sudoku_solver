#include <Group.h>

void Group::addCell(Cell & cell)
{
	// Add Cell to Group
	this->cells.push_back( &cell );

	// Add the Group to Cell Group list
	cell.addToGroup( *this );
}

Cell Group::getCell(const unsigned i) const
{
	return *( this->cells[i] );
}

unsigned Group::getNumberOfCell(void) const
{
	return this->cells.size();
}

CellPtrVector Group::getCells(void)
{
	return this->cells;
}

bool operator==(Group left , Group right)
{
	if( left.getCells() != right.getCells() ) return false;
	
	return true;
}

bool operator!=(Group left , Group right)
{
	return !(left==right);
}
