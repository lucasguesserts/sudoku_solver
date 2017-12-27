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
	unsigned defaultRow = 0;
	unsigned defaultColumn = 0;

	checkEqual( c.getRow() , defaultRow );
	checkEqual( c.getColumn() , defaultColumn );
	checkEqual( c.getValue() , defaultValue );
	checkEqual( c.getPossibleValues() == allPossibleValues , true );
}

TestCase( CellCopy )
{
	Cell c1(3,4);
	Cell c2(c1);
	Cell c3 = c1;
	check(c1 == c2);
	check(c1 == c3);
}


TestCase( CellRowColumnConstructor )
{
	Position pos(3,4);
	Cell c ( pos.row, pos.column );
	
	checkEqual(c.getRow() , pos.row);
	checkEqual(c.getColumn() , pos.column);
	checkEqual(c.getValue() , 0);
	checkEqual( c.getPossibleValues() == allPossibleValues , true );
	
	pos.set(8,1);
	c.setPosition(pos.row , pos.column);
	
	checkEqual(c.getRow() , pos.row);
	checkEqual(c.getColumn() , pos.column);
}

TestCase( CellSetAndGetValue )
{
	unsigned value = 6;
	Cell c;

	c.setValue(value);
	checkEqual(c.getValue() , value);
	// After using 'setValue' function, the
	// possibleValues set is cleared
	checkEqual(c.getPossibleValues().size() , 0);
}

TestCase( GetPossibleValues )
{
	Cell c;

	checkEqual( c.getPossibleValues() == allPossibleValues , true );
}

TestCase( GetPossibleValue )
{
	Cell c;

	checkEqual( c.getPossibleValue(0) , *(allPossibleValues.begin()) );
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

TestCase( CellNumberOfPossibleValues )
{
	Cell c;
	unsigned defaultSize = allPossibleValues.size();

	checkEqual( c.getNumberOfPossibleValues() , defaultSize );
}

TestCase( AddToGroupAndGetGroup )
{
	// Create Cell and Group
	Cell c(1,2);
	Group g;

	// add Group to Cell:GroupPtrVector
	c.addToGroup( g );

	// check
	checkEqual( c.getGroup(0) == g , true );
}

TestCase( CellIsEqualAndIsDifferentOperators )
{
	Cell c[3];

	checkEqual( c[0] == c[1] , true );
	checkEqual( c[0] == c[2] , true );

	Position pos0(1,0);
	Position pos1(0,5);
	c[1].setPosition(pos0.row , pos0.column);
	c[2].setPosition(pos1.row , pos1.column);

	checkEqual( c[0] != c[1] , true );
	checkEqual( c[0] != c[2] , true );
}

// ############### Group ###############

TestCase( GroupAddCellAndGetCell )
{
	Group g;

	unsigned x = 3;
	unsigned y = 2;
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
	unsigned x0 = 1;
	unsigned x1 = 5;

	unsigned y0 = 8;
	unsigned y1 = 4;

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
	checkEqual( g.getCells() == testVector , true );
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
	checkEqual( g0 == g1 , true );
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
	unsigned row = 3;
	unsigned column = 2;
	Cell testCell(row , column);
	Cell csg = sg.getCell(row , column);
	checkEqual( csg == testCell , true );
}

TestCase( SudokuGamePosition )
{
	SudokuGame sg(N_VALUES);
	for(unsigned row=0 ; row<N_VALUES ; ++row)
	{
		for (unsigned column=0 ; column<N_VALUES ; ++column)
		{
			checkEqual( sg.getCell(row,column).getRow() , row );
			checkEqual( sg.getCell(row,column).getColumn() , column );
		}
	}
}

TestCase( SudokuGameGetCellNumberOfPossibleValues )
{
	// Create a SudokuGame ang test the
	// number of possible values of a
	// Cell
	SudokuGame sg;
	unsigned l=2 , c=3;
	unsigned defaultSize = allPossibleValues.size();

	checkEqual( sg.getCellNumberOfPossibleValues(l,c) , defaultSize );
}

TestCase( SudouGameSetCellValue )
{
	SudokuGame sg;
	unsigned l = 3; unsigned rectangleLine = 1;
	unsigned c = 4; unsigned rectangleColumn = 1;
	unsigned value = 2;

	// Set Cell value
	sg.setCellValue(l , c , value);

	// Check Cell value
	checkEqual( sg.getCell(l,c).getValue() , value );

	// for each Cell in line 'l', verifies
	// if 'value' is a possible value
	foreach( Cell * cell , sg.getLine(l).getCells() )
	{
		checkEqual( cell->havePossibleValue(static_cast<unsigned>(value)) , false);
	}

	// for each Cell in column 'c', verifies
	// if 'value' is a possible value
	foreach( Cell * cell , sg.getColumn(c).getCells() )
	{
		checkEqual( cell->havePossibleValue(static_cast<unsigned>(value)) , false);
	}

	// for each Cell in rectancle, verifies
	// if 'value' is a possible value
	foreach( Cell * cell , sg.getRectangle(rectangleLine , rectangleColumn).getCells() )
	{
		checkEqual( cell->havePossibleValue(static_cast<unsigned>(value)) , false);
	}
}

TestCase( SudokuGameGetCellUniquePossibleValue )
{
	// 1. Create a SudokuGame
	// Caution, this test may fail
	// if the sudoku game size
	// is 9 (N_VALUES=9)
	SudokuGame sg;

	// 2. Make a cell has a unique possible value
	unsigned l = 2;
	for(unsigned c=0 ; c<(N_VALUES-1) ; ++c)
	{
		sg.setCellValue(l , c , c+1);
	}

	// 3. Test
	checkEqual( sg.getCellUniquePossibleValue(l,8) , N_VALUES );
}

TestCase( SudokuGameLine )
{
	// Create a SudokuGame
	unsigned size = 9;
	SudokuGame sg(size);
	// Get a SudouGame Line
	unsigned l = 2;
	Line line = sg.getLine(l);

	// For each Cell in line, verify if
	// the line Cell is the same as got
	// by the Line::getCell
	for(unsigned c=0 ; c<size ; ++c)
	{
		checkEqual( sg.getCell(l,c) == line.getCell(c) , true );
	}

	// Verify for each Cell in line if
	// it belongs to the line
	for(unsigned c=0 ; c<size ; ++c)
	{
		Cell cell = sg.getCell(l,c);
		checkEqual( cell.getGroup(0) == line , true );
	}
}

TestCase( SudokuGameSetCellValue )
{
	// Create a SudouGame. It has Cells and Lines
	SudokuGame sg(9);

	// Get a line
	unsigned l = 3;
	Line line = sg.getLine( l );

	// Set a 'line' Cell value
	unsigned c = 2;
	unsigned value = 1;
	Cell cell = line.getCell( c );
	cell.setValue( value );

	// Verify for each 'line' Cell if the
	// value 'value' was removed from
	// PossibleValues list
	// Initialize the correct possibleValues list
	unsigned nValues = 8;
	unsigned first = 2;
	PossibleValuesListStruct pvList(first , nValues);
	PossibleValues pv(pvList.list , pvList.list+nValues);
	foreach( Cell * lc , line.getCells() )
	{
		if( lc == &cell ) continue; // pass the cell that
									// the value was set.
		checkEqual( lc->getPossibleValues() == pv , true );
	}
}

TestCase( SudokuGameRectangle )
{
	// Create a SudokuGame
	SudokuGame sg;

	// Get a Rectangle
	unsigned l = 1;
	unsigned c = 2;
	Rectangle rec = sg.getRectangle(l,c);

	// Get all rectangleCells and verify
	// if the line and column number are correct
	unsigned defaultSize = 3;
	for(unsigned cl=0 ; cl<defaultSize ; ++cl)
	{
		for(unsigned cc=0 ; cc<defaultSize ; ++cc)
		{
			checkEqual( rec.getCell(cc + cl*defaultSize).getColumn() , cc + c*defaultSize );
			checkEqual( rec.getCell(cc + cl*defaultSize).getRow() , cl + l*defaultSize );
		}
	}

}

// Refactoring needed!!!!!!!!!!!!!!!!!!!!!!!
TestCase( WriteSudokuGame )
{
	SudokuGame sg1, sg2;

	sg1.setCellValue(2,3,5);

	sg1.write("empty_sudoku_game.sudokugame");
	sg2.read("empty_sudoku_game.sudokugame");

	checkEqual( sg2.getCell(2,3).getValue() , 5 );
}

TestCase( CreateGameFromArray )
{
	unsigned game[9][9] = {
		{0,0,4,0,6,0,0,5,8},
		{3,0,0,8,9,0,0,1,7},
		{1,0,8,0,0,0,0,0,2},
		{0,2,5,0,1,8,0,0,6},
		{0,0,0,6,0,0,9,0,0},
		{7,6,0,0,4,0,0,2,1},
		{6,0,0,0,3,4,0,0,9},
		{0,0,7,0,8,9,1,0,3},
		{9,0,2,0,7,0,0,0,0}
		};
	SudokuGame sg;
	sg.setUsingArray(game);

	checkEqual( sg.getCell(1,0).getValue() , 3 );
	checkEqual( sg.getCell(2,2).getValue() , 8 );
	checkEqual( sg.getCell(8,4).getValue() , 7 );

	checkEqual( sg.getCell(2,5).getNumberOfPossibleValues() , 3 );
	checkEqual( sg.getCell(5,2).getNumberOfPossibleValues() , 2 );

	sg.write("easy.sudokugame");
}
