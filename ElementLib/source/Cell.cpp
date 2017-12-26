#include <Cell.h>

// Constructors

Cell::Cell( void )
	: x(-1) , y(-1) , value(0), possibleValues(allPossibleValues)
{
}

Cell::Cell(const int  x, const int y)
	: value(0), possibleValues(allPossibleValues)
{
	this->setx(x);
	this->sety(y);
}

// set and get properties functionalities

void Cell::setValue( const int value )
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

void Cell::setx( const int x )
{
	this->x = x;
}

int Cell::getx( void ) const
{
	return this->x;
}

void Cell::sety( const int y )
{
	this->y = y;
}

int Cell::gety( void ) const
{
	return this->y;
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
	int size = this->possibleValues.size();
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

Group Cell::getGroup(const int i)
{
	return *(this->group[i]);
}

bool operator==(Cell left , Cell right)
{
	if( left.getx() != right.getx() ) return false;
	if( left.gety() != right.gety() ) return false;
//	if( left.getValue() != right.getValue() ) return false;
//	if( left.getPossibleValues() != right.getPossibleValues() ) return false;

	return true;
}

bool operator!=(Cell left , Cell right)
{
	return !(left==right);
}
