#ifndef CELL_H
#define CELL_H

#include <PossibleValues.h>

class Cell
{
public:
	
		Cell(void);
		Cell(const int , const int);
		
		void			setValue( const int );
		int				getValue( void ) const;
		
		void			setx( const int );
		int				getx(void) const;
		
		void			sety( const int );
		int				gety(void) const;

		PossibleValues	getPossibleValues(void) const;
		void			erasePossibleValue(const unsigned);
		bool			havePossibleValue(unsigned) const;
		
	private:
		int				value;
		int				x;
		int				y;
		PossibleValues	possibleValues;
};

bool operator==(Cell left , Cell right);
bool operator!=(Cell left , Cell right);

#endif
