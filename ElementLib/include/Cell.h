#ifndef CELL_H
#define CELL_H

#include <vector>
#include <exception>

#include <PossibleValues.h>

class Group;

class Cell
{
public:
		Cell(void);
		
		void					setValue( const unsigned value );
		unsigned				getValue( void ) const;
		
		unsigned				getNumberOfPossibleValues(void) const;
		unsigned				getUniquePossibleValue(void) const;
		void					erasePossibleValue(const unsigned);

		std::vector<Group *>	getGroups(void) const;
		void					addToGroup(Group & g);

		bool					isValid(void) const;
		
	private:
		unsigned				value;
		PossibleValues			possibleValues;
		std::vector<Group *>	group;

		bool 					isValueValid(const unsigned value) const;
};

#include <Group.h>

#endif
