#ifndef POSSIBLE_VALUES_H
#define POSSIBLE_VALUES_H

#include <set>

class PossibleValues:
	public std::set<unsigned>
{
	public:
		PossibleValues(void);
		unsigned uniqueValue(void) const;
		static const unsigned firstValue;
		static const unsigned lastValue;
		static const unsigned numberOfValues;
};

#endif
