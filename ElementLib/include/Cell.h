#ifndef CELL_H
#define CELL_H

// std
#include <vector>
using std::vector;

// Utils
#include <Foreach.h>
#include <PossibleValues.h>

class Group;
typedef vector<Group *> GroupPtrVector;

class Cell
{
public:
		// Constructors
		Cell(void);
		
		// set and get properties functionalities
		void			setValue( const unsigned );
		unsigned		getValue( void ) const;
		
		// PossibleValues functionalities
		PossibleValues	getPossibleValues(void) const;
		unsigned		getPossibleValue(unsigned) const;
		void			erasePossibleValue(const unsigned);
		bool			havePossibleValue(unsigned) const;
		unsigned		getNumberOfPossibleValues(void) const;

		// Group functionalities
		void			addToGroup(Group & g);
		Group			getGroup(const unsigned i) const;
		GroupPtrVector	getGroups(void) const;
		
	private:
		unsigned		value;
		PossibleValues	possibleValues;
		GroupPtrVector	group;
};

#include <Group.h>

#endif
