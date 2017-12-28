#include <Cell.h>

// Constructors

Cell::Cell( void )
	: value(0), possibleValues(allPossibleValues)
{
}

void Cell::setValue( const unsigned value )
{
	if(value == 0) return;
	else
	{
		this->value = value;
		this->possibleValues.clear();
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

Group Cell::getGroup(const unsigned i) const
{
	return *(this->group[i]);
}

GroupPtrVector Cell::getGroups(void) const
{
	return this->group;
}
