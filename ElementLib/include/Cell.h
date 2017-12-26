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
		Cell(const unsigned , const int);
		
		// set and get properties functionalities
		void			setValue( const unsigned );
		unsigned		getValue( void ) const;
		
		void			setx( const unsigned );
		unsigned		getx(void) const;
		
		void			sety( const unsigned );
		unsigned		gety(void) const;

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
		// properties
		unsigned		value;
		unsigned		x;
		unsigned		y;
		// PossibleValues
		PossibleValues	possibleValues;
		// Groups
		GroupPtrVector	group;
};

// Two Cells are equal when they are located
// in the same place, that is, when 'x' and
// 'y' are equal.
bool operator==(Cell left , Cell right);
bool operator!=(Cell left , Cell right);

#include <Group.h>

#endif
