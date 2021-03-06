#include <Cell.h>

Cell::Cell( void )
	: value(0)
{
}

void Cell::setValue( const unsigned value )
{
	if(value == 0) return;
	if( ! (this->isValueValid(value)) ) throw "Invalid value inserted";
	else{
		this->value = value;
		this->possibleValues.clear();
		for( Group * cellGroups : this->group )
			for( Cell * c : cellGroups->getCells() )
				c->erasePossibleValue( value );
	}
	return;
}

unsigned Cell::getValue( void ) const
{
	return this->value;
}

unsigned Cell::getNumberOfPossibleValues(void) const
{
	return this->possibleValues.size();
}

unsigned Cell::getUniquePossibleValue(void) const
{
	return this->possibleValues.uniqueValue();
}

std::vector<Group *> Cell::getGroups(void) const
{
	return this->group;
}

void Cell::erasePossibleValue(const unsigned val)
{
	this->possibleValues.erase( val );
}

bool Cell::hasPossibleValue(const unsigned value)
{
	bool has = false;
	if(this->possibleValues.count(value) > 0)
		has = true;
	return has;
}

void Cell::addToGroup(Group & g)
{
	this->group.push_back( &g );
}

bool Cell::isValid(void) const
{
	bool vality = true;
	if(this->value == 0) vality = true;
	else
	{
		for( Group * cellGroup : this->group )
			for( Cell * cellInSameGroup : cellGroup->getCells() )
			{
				if (cellInSameGroup == this) continue;
				unsigned cellInSameGroupValue = cellInSameGroup->getValue();
				if (cellInSameGroupValue == 0) continue;
				if (this->value == cellInSameGroupValue) vality = false;
			}
	}
	return vality;
}

bool Cell::isValueValid(const unsigned value) const
{
	bool vality;
	if(value<PossibleValues::firstValue || value>PossibleValues::lastValue)
		vality = false;
	else
		vality = true;
	return vality;
}
