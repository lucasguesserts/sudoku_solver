#ifndef POSSIBLE_VALUES_H
#define POSSIBLE_VALUES_H

#include <set>

class PossibleValues:
	public std::set<unsigned>
{
	public:
		PossibleValues(void);
		unsigned uniqueValue(void);
};

#endif
