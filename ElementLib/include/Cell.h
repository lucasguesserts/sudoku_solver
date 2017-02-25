#ifndef CELL_H
#define CELL_H

#include <vector>
using std::vector;

#include <PossibleValues.h>

class Group;
typedef vector<Group *> GroupPtrVector;

class Cell
{
public:
		// Constructors
		Cell(void);
		Cell(const int , const int);
		
		// set and get properties functionalities
		void			setValue( const int );
		int				getValue( void ) const;
		
		void			setx( const int );
		int				getx(void) const;
		
		void			sety( const int );
		int				gety(void) const;

		// PossibleValues functionalities
		PossibleValues	getPossibleValues(void) const;
		void			erasePossibleValue(const unsigned);
		bool			havePossibleValue(unsigned) const;

		// Group functionalities
		void			addToGroup(Group & g);
		Group			getGroup(const int i);
//		GroupPtrVector	getGroupPtrVector(void);
		
	private:
		// properties
		int				value;
		int				x;
		int				y;
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
