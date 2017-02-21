#define BOOST_TEST_MODULE TestModule

// std
#include <iostream>
using std::cout;
using std::endl;

// ElementLib
#include <Cell.h>
#include <SudokuGame.h>

// Utils
#include <Test.h>

// Cell

TestCase( CellVoidConstructor )
{
	Cell c;
	unsigned defaultValue = 0;
	unsigned defaultX = -1;
	unsigned defaultY = -1;

	checkEqual( c.getx() , defaultX );
	checkEqual( c.gety() , defaultY );
	checkEqual( c.getValue() , defaultValue );
	check( c.getPossibleValues() == allPossibleValues );
}

TestCase( CellXYConstructor )
{
	int x = 3;
	int y = 4;
	Cell c ( x , y );
	
	checkEqual(c.getx() , x);
	checkEqual(c.gety() , y);
	checkEqual(c.getValue() , 0);
	check( c.getPossibleValues() == allPossibleValues );
	
	x = 8;
	y = 1;
	c.setx(x);
	c.sety(y);
	
	checkEqual(c.getx() , x);
	checkEqual(c.gety() , y);
}

TestCase( CellSetAndGet )
{
	int value = 6;
	Cell c;

	c.setValue(value);
	checkEqual(c.getValue() , value);
	// After using 'setValue' function, the
	// possibleValues set is cleared
	checkEqual(c.getPossibleValues().size() , 0);
}

//TestCase( possibleValues )
//{
//	Cell c;
//	PossibleValues pv = c.getPossibleValues();
//	PossibleValues::iterator it;
//	PossibleValues::iterator begin = pv.begin();
//	PossibleValues::iterator end = pv.end();
//	for(it = begin ; it!=end ; ++it)
//	{
//		cout << *it << endl;
//	}
//}

TestCase( HavePossibleValue )
{
	Cell c;
	checkEqual( c.havePossibleValue(firstPossibleValue) , true );
}

TestCase( ErasePossibleValue )
{
	Cell c;
	unsigned valErase = 3;
	unsigned val = 4;
	c.erasePossibleValue(valErase);
	checkEqual( c.havePossibleValue(valErase) , false);
	checkEqual( c.havePossibleValue(val) , true);
}

TestCase( CellIsEqualAndIsDifferentperators )
{
	Cell c[5];

	checkEqual( c[0] == c[1] , true );
	checkEqual( c[0] == c[2] , true );
	checkEqual( c[0] == c[3] , true );
	checkEqual( c[0] == c[4] , true );

	int val = 2;
	int x = 1;
	int y = 5;
	c[1].erasePossibleValue(val);
	c[2].setValue(val);
	c[3].setx(x);
	c[4].sety(y);

	checkEqual( c[0] != c[1] , true );
	checkEqual( c[0] != c[2] , true );
	checkEqual( c[0] != c[3] , true );
	checkEqual( c[0] != c[4] , true );
}

// SudokuGame

TestCase( SudokuGameVoidConstructor )
{
	SudokuGame sg;
	int		x = 3;
	int		y = 0;
	Cell	testCell(x , y);
	Cell	csg = sg.getCell(x , y);

	checkEqual( csg == testCell , true );
	
}

TestCase( SudokuGameConstructorWithInt )
{
	SudokuGame sg(4);
	int		x=2;
	int		y=1;
	Cell	testCell(x , y);
	Cell	csg = sg.getCell(x , y);

	checkEqual( csg == testCell , true );

}

// getCell already tested...


