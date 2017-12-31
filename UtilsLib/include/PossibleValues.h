#ifndef POSSIBLE_VALUES
#define POSSIBLE_VALUES

#include <set>

class PossibleValues:
	public std::set<unsigned>
{
	PossibleValues(void);
	unsigned uniqueValue(void);
}

#endif
