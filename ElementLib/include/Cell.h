#include <set>

using std::set;

typedef set<int> IntSet;

const int allValues[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
const int numberOfAllValues = 9;
const IntSet allValuesSet(allValues, allValues + 9);

class Cell
{
public:
	
		Cell(void);
		Cell(const int , const int);
		
		void	setValue( const int );
		int		getValue( void ) const;
		
		void	setx( const int );
		int		getx(void) const;
		
		void	sety( const int );
		int		gety(void) const;

		IntSet	getPossibleValues(void) const;
		
	private:
		int		value;
		int		x;
		int		y;
		IntSet	possibleValues;
};