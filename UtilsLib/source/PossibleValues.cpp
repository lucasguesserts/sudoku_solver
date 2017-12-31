#include <PossibleValues.h>

const unsigned PossibleValues::firstValue = 1;
const unsigned PossibleValues::lastValue = 9;


PossibleValues::PossibleValues(void)
{
	for (unsigned value=PossibleValues::firstValue ; value<=PossibleValues::lastValue ; ++value)
		this->insert(value);
}

unsigned PossibleValues::uniqueValue(void)
{
	if (this->size() == 1)
		return *(this->cbegin());
	else
		throw "Not unique possible value accessed.";
}
