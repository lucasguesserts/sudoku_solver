#define BOOST_TEST_MODULE TestModule

//// std
//#include <iostream>
//using std::cout;
//using std::endl;

// ElementLib
#include <Cell.h>
#include <SudokuGame.h>
#include <Group.h>

// Utils
#include <Test.h>


// ############### Cell ###############


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

TestCase( GetPossibleValues )
{
	Cell c;

	checkEqual( c.getPossibleValues() , allPossibleValues );
}

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

TestCase( AddToGroupAndGetGroup )
{
	// Create Cell and Group
	Cell c(1,2);
	Group g;

	// add Group to Cell:GroupPtrVector
	c.addToGroup( g );

	// check
	ckeckEqual( c.getGroup(0) , g );
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

// ############### Group ###############

TestCase( GroupAddCellAndGetCell )
{
	Group g;

	int x = 3;
	int y = 2;
	Cell testCell(x , y);
	Cell gotCell;

	g.addCell(testCell);
	gotCell = g.getCell(0);

	checkEqual( testCell == gotCell , true );
}

TestCase( GroupGetNumberOfCells )
{
	// Create Cells
	Cell c0(1,2);
	Cell c1(3,4);
	Cell c2(5,6);

	// Add Cells to a Group
	Group g;

	g.addCell(c0);
	g.addCell(c1);
	g.addCell(c2);

	// check
	checkEqual( g.getNumberOfCell() , 3 );
}

TestCase( GroupGetCells )
{
	// Creating test Cells
	int x0 = 1;
	int x1 = 5;

	int y0 = 8;
	int y1 = 4;

	Cell c0(x0 , y0);
	Cell c1(x1 , y1);

	// Create Group
	Group g;
	g.addCell(c0);
	g.addCell(c1);

	// Create test vector
	CellPtrVector testVector;
	testVector.push_back( &c0 );
	testVector.push_back( &c1 );

	// Test
	checkEqual( g.getCells() , testVector );
}

TestCase( GroupIsEqualAndIsDifferentOperators )
{
	// A Group is diferenciated by
	// the Cells that it contains
	Cell c0(1,2);
	Cell c1(5,3);
	Cell c2(4,3);

	Group g0 , g1 , g2;

	// Add Cells
	g0.addCell(c0);
	g1.addCell(c0);
	g2.addCell(c0);
	g2.addCell(c1);

	// Check
	checkEqual( g0 , g1 );
	checkEqual( g0 != g2 , true );
}

TestCase( CellAndGroupAdd )
{
	// A Group will add Cells, and then it
	// will know which Cells it contains.
	// The add Cell also must know to
	// what Groups it belongs. Therefore,
	// the Group::addCell must in some way
	// tell the added Cell that now it
	// belongs to the Group.
	//
	// The command Group::addCell will
	// add the Cell to Group and the Group
	// to Cell Groups.

	Group g;
	Group gWrong;

	int x = 3;
	int y = 4
	Cell cWrong;
	Cell c(3,4);

	g.addCell(c);

	// Check Group getCell
	checkEqual( g.getCell(0) == c , true );
	checkEqual( g.getCell(0) == cWrong , false );

	// Check if the Cell knows to which
	// Group it belongs
	checkEqual( c.getGroup(0) == g , true );
	checkEqual( c.getGroup(0) == gWrong , false );
}

// ############### SudokuGame ###############

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
	// SudokuGame
	SudokuGame sg(4);

	// Test Cell
	int		x = 2;
	int		y = 1;
	Cell	testCell(x,y);

	// check
	Cell csg = sg.getCell(x,y);
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
