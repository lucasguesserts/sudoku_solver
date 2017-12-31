#include <PossibleValues.h>

PossibleValues::PossibleValues(void)
{
	unsigned firstValue = 1;
	unsigned lastValue = 9;
	for (unsigned value=firstValue ; value<=lastValue ; ++value)
		this->insert(value);
}

unsigned PossibleValues::uniqueValue(void)
{
	if (this->size() == 1)
		return *(this->cbegin());
	else
		throw "Not unique possible value accessed.";
}
