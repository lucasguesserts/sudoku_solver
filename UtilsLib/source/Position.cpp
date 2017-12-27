#include "Position.h"

Position::Position(const unsigned row, const unsigned column)
{
	this->set(row,column);
}

void Position::set(const unsigned row, const unsigned column)
{
	this->row = row;
	this->column = column;
}
