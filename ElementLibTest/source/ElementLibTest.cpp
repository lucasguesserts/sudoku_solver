#define BOOST_TEST_MODULE TestModule

//// std
//#include <iostream>
//using std::cout;
//using std::endl;

// ElementLib
#include <Cell.h>

// Boost
#include <Test.h>

TestCase( CellSetAndGet )
{
	int value = 6;
	Cell c;

	checkEqual(c.getValue(), 0);

	c.setValue(value);
	checkEqual(c.getValue() , value);
}

TestCase( CellConstructor )
{
	int x = 3;
	int y = 4;
	Cell c ( x , y );
	
	checkEqual(c.getx() , x);
	checkEqual(c.gety() , y);
	checkEqual(c.getValue() , 0);
	
	x = 8;
	y = 1;
	c.setx(x);
	c.sety(y);
	
	checkEqual(c.getx() , x);
	checkEqual(c.gety() , y);
}
