#include <Cell.h>

Cell::Cell( void )
	: x(-1) , y(-1)
{
}

Cell::Cell( const int  x, const int y)
{
	this->setx(x);
	this->sety(y);
}

void Cell::setValue( const int value )
{
	this->value = value;
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