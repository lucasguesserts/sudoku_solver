#ifndef POSSIBLE_VALUES
#define POSSIBLE_VALUES

#include <set>

#define FIRST_VALUE 1u
#define N_VALUES 9u

using std::set;

typedef set<unsigned> PossibleValues;

struct PossibleValuesListStruct
{
	public:

	PossibleValuesListStruct(unsigned first , unsigned n)
	{
		this->list = new unsigned[n];
		for(unsigned i=0 ; i<(n) ; ++i){
			list[i] = i + first;
		}
	}

	~PossibleValuesListStruct()
	{
		delete[] this->list;
	}

	unsigned *list;
};

const PossibleValuesListStruct possibleValuesList(FIRST_VALUE , N_VALUES);
const PossibleValues allPossibleValues (possibleValuesList.list , possibleValuesList.list+N_VALUES);
const unsigned firstPossibleValue		=	*(allPossibleValues.begin());
const unsigned lastPossibleValue		=	*(allPossibleValues.end());
const unsigned numberOfPossibleValues	=	N_VALUES;

#endif