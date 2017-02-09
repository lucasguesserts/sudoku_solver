#define BOOST_TEST_MODULE TestModule

// boost
#include <Test.h>

TestCase( CheckEqualAndCheckClose ){
	double i = 0;
	double j = 0;

	checkClose( i , j , 1.0e-12 );
	checkEqual( i , j );
}
