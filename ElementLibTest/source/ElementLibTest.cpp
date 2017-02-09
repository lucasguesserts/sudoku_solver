#define BOOST_TEST_MODULE TestModule

// ElementLib
#include <Cell.h>

// Boost
#include <Test.h>

TestCase( CellTest )
{
	int value = 6;
	Cell c;

	c.set(value);
	checkEqual(c.get() , value);
}
