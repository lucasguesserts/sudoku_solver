#include <Cell.h>

// Constructors

Cell::Cell(const unsigned  row, const unsigned column)
	: position(row,column), value(0), possibleValues(allPossibleValues)
{
}

// set and get properties functionalities

void Cell::setValue( const unsigned value )
{
	if(value == 0) return;
	else
	{
		// Set value
		this->value = value;

		// Clear possible values set
		this->possibleValues.clear();

		// Remove the 'value' from
		// PossibleValue of each Cell
		// that belongs to this Cell
		// Groups
		foreach( Group * g , this->group )
		{
			foreach( Cell * c , g->getCells() )
			{
				c->erasePossibleValue( value );
			}
		}
	}
}

unsigned Cell::getValue( void ) const
{
	return this->value;
}

// Position

void Cell::setPosition(const unsigned row, const unsigned column)
{
	this->position.set(row,column);
}

Position Cell::getPosition(void) const
{
	return this->position;
}

unsigned Cell::getRow(void) const
{
	return this->position.row;
}

unsigned Cell::getColumn(void) const
{
	return this->position.column;
}

// PossibleValues functionalities

PossibleValues Cell::getPossibleValues(void) const
{
	return this->possibleValues;
}

unsigned Cell::getPossibleValue(unsigned pos) const
{
	// Return the possible value in position 'pos'
	// in set. It will be useful to get the
	// unique possible value (when the set
	// has only one element.
	unsigned size = this->possibleValues.size();
	PossibleValues::iterator it = this->possibleValues.begin();

	if (pos < size)	return *it;
	else throw "Trying to get a possible value out of range!";
}

void Cell::erasePossibleValue(const unsigned val)
{
	this->possibleValues.erase( val );
}

bool Cell::havePossibleValue(unsigned val) const
{
	return static_cast<bool>( this->possibleValues.count(val) );
}

unsigned Cell::getNumberOfPossibleValues(void) const
{
	return this->possibleValues.size();
}

// Group functionalities

void Cell::addToGroup(Group & g)
{
	this->group.push_back( &g );
}

Group Cell::getGroup(const unsigned i)
{
	return *(this->group[i]);
}

bool operator==(Cell left , Cell right)
{
	if( left.getPosition() != right.getPosition() ) return false;
//	if( left.getValue() != right.getValue() ) return false;
//	if( left.getPossibleValues() != right.getPossibleValues() ) return false;

	return true;
}

bool operator!=(Cell left , Cell right)
{
	return !(left==right);
}
