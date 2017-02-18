#include <Cell.h>

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

void Cell::setValue( const int value )
{
	this->value = value;
	// Clear possible values set
	this->possibleValues.clear();
}

int Cell::getValue( void ) const
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

PossibleValues Cell::getPossibleValues(void) const
{
	return this->possibleValues;
}


void Cell::erasePossibleValue(const unsigned val) const
{
	this->getPossibleValues().erase( val );
}
