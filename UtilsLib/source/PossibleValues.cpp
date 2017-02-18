#include <PossibleValues.h>

bool operator== (PossibleValues left , PossibleValues right)
{

	if ( left.size() != right.size() )
		return false;

	PossibleValues::iterator itLeft		= left.begin();
	PossibleValues::iterator itRight	= right.begin();
	for( ; itLeft != left.end() ; ++itLeft , ++itRight )
	{
		if( *itLeft != *itRight )
			return false;
	}

	return true;
}
