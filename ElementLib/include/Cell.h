#ifndef CELL_H
#define CELL_H

// std
#include <vector>
using std::vector;

// Utils
#include <Foreach.h>
#include <PossibleValues.h>
#include <Position.h>

class Group;
typedef vector<Group *> GroupPtrVector;

class Cell
{
public:
		// Constructors
		Cell(const unsigned row = 0, const unsigned column = 0);
		
		// set and get properties functionalities
		void			setValue( const unsigned );
		unsigned		getValue( void ) const;
		
		void			setPosition(const unsigned row, const unsigned column);
		Position		getPosition(void) const;
		unsigned		getRow(void) const;
		unsigned		getColumn(void) const;

		// PossibleValues functionalities
		PossibleValues	getPossibleValues(void) const;
		unsigned		getPossibleValue(unsigned) const;
		void			erasePossibleValue(const unsigned);
		bool			havePossibleValue(unsigned) const;
		unsigned		getNumberOfPossibleValues(void) const;

		// Group functionalities
		void			addToGroup(Group & g);
		Group			getGroup(const unsigned i);

		
	private:
		unsigned		value;
		Position		position;
		PossibleValues	possibleValues;
		GroupPtrVector	group;
};

// Two Cells are equal when they are located
// in the same place, that is, when 'x' and
// 'y' are equal.
bool operator==(Cell left , Cell right);
bool operator!=(Cell left , Cell right);

#include <Group.h>

#endif
