#define BOOST_TEST_MODULE TestModule

// std
#include <iostream>
using std::cout;
using std::endl;

// ElementLib
#include <Cell.h>
#include <SudokuGame.h>
#include <Group.h>

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
	Cell c[3];

	checkEqual( c[0] == c[1] , true );
	checkEqual( c[0] == c[2] , true );

	int x = 1;
	int y = 5;
	c[1].setx(x);
	c[2].sety(y);

	checkEqual( c[0] != c[1] , true );
	checkEqual( c[0] != c[2] , true );
}

// SudokuGame

TestCase( SudokuGameDefaultConstructor )
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

// SudokuGame::getCell already tested...

TestCase( SudokuGameLine )
{
	int size = 9;
	int l = 2;
	SudokuGame sg(size);
	Line line = sg.getLine(l);

	for(int c=0 ; c<size ; ++c)
	{
		checkEqual( sg.getCell(l,c) == line.getCell(c) , true );
	}
}

// Group

TestCase( GroupAddCellAndGetCell )
{
	SudokuGame sg(9);
	Group g;

	int x = 3;
	int y = 2;
	Cell testCell = sg.getCell(x , y);
	Cell gotCell;

	g.addCell(testCell);
	gotCell = g.getCell(0);

	checkEqual( testCell == gotCell , true );

}
