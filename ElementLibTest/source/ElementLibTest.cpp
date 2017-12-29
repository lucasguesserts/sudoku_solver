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
	checkEqual( c.getValue() , defaultValue );
	checkEqual( c.getPossibleValues() == allPossibleValues , true );
}

TestCase( CellSetAndGetValue )
{
	unsigned value = 6;
	Cell c;
	c.setValue(value);
	checkEqual(c.getValue() , value);
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
	Cell c;
	Group g;
	g.addCell( c );
	checkEqual( c.getGroup(0).getNumberOfCell() , 1 );
}

// ############### Group ###############

TestCase( GroupAddCellAndGetCell )
{
	const unsigned value = 3;
	Group g;
	Cell testCell;
	testCell.setValue(value);
	g.addCell(testCell);
	Cell gotCell = g.getCell(0);
	checkEqual( gotCell.getValue() , value );
}

TestCase( GroupGetNumberOfCells )
{
	Cell c0, c1, c2;
	Group g;
	g.addCell(c0);
	g.addCell(c1);
	g.addCell(c2);
	checkEqual( g.getNumberOfCell() , 3 );
}

TestCase( GroupGetCellValue )
{
	const unsigned value = 8;
	Group g;
	Cell c;
	g.addCell(c);
	c.setValue(value);
	checkEqual( g.getCellValue(0) , value );
}

// ############### SudokuGame ###############

TestCase( SudokuGameGetCellNumberOfPossibleValues )
{
	SudokuGame sg;
	const unsigned r=2 , c=3;
	const unsigned defaultSize = allPossibleValues.size();
	checkEqual( sg.getCellNumberOfPossibleValues(r,c) , defaultSize );
}

TestCase( SudouGameSetCellValue )
{
	SudokuGame sg;
	const unsigned r = 3; const unsigned rectangleRow = 1;
	const unsigned c = 4; const unsigned rectangleColumn = 1;
	const unsigned value = 2;

	sg.setCellValue(r , c , value);
	checkEqual( sg.getCell(r,c).getValue() , value );

	foreach( Cell * cell , sg.getRow(r).getCells() )
	{
		checkEqual( cell->havePossibleValue(value) , false);
	}

	foreach( Cell * cell , sg.getColumn(c).getCells() )
	{
		checkEqual( cell->havePossibleValue(value) , false);
	}

	foreach( Cell * cell , sg.getRectangle(rectangleRow , rectangleColumn).getCells() )
	{
		checkEqual( cell->havePossibleValue(value) , false);
	}
}

TestCase( SudokuGameGetCellUniquePossibleValue )
{
	SudokuGame sg;
	const unsigned r = 2;
	for(unsigned c=0 ; c<(N_VALUES-1) ; ++c)
	{
		sg.setCellValue(r , c , c+1);
	}
	checkEqual( sg.getCellUniquePossibleValue(r,8) , N_VALUES );
}

TestCase( SudokuGameSetCellValue )
{
	const unsigned r = 3;
	const unsigned c = 2;
	const unsigned value = 1;
	SudokuGame sg;
	Row row = sg.getRow(r);
	Column column = sg.getColumn(c);
	sg.setCellValue(r,c,value);
	checkEqual(row.getCellValue(c) , value);
	checkEqual(column.getCellValue(r) , value);
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
	unsigned game[] = {
		0,0,4,0,6,0,0,5,8,
		3,0,0,8,9,0,0,1,7,
		1,0,8,0,0,0,0,0,2,
		0,2,5,0,1,8,0,0,6,
		0,0,0,6,0,0,9,0,0,
		7,6,0,0,4,0,0,2,1,
		6,0,0,0,3,4,0,0,9,
		0,0,7,0,8,9,1,0,3,
		9,0,2,0,7,0,0,0,0
		};
	SudokuGame sg;
	sg.set(game);
	sg.write("easy.sudokugame");
	checkEqual( sg.getCell(1,0).getValue() , 3 );
	checkEqual( sg.getCell(2,2).getValue() , 8 );
	checkEqual( sg.getCell(8,4).getValue() , 7 );
	checkEqual( sg.getCell(2,5).getNumberOfPossibleValues() , 3 );
	checkEqual( sg.getCell(5,2).getNumberOfPossibleValues() , 2 );
}

TestCase( CreateGameFromVector )
{
	vector<unsigned> game = {
		0,0,4,0,6,0,0,5,8,
		3,0,0,8,9,0,0,1,7,
		1,0,8,0,0,0,0,0,2,
		0,2,5,0,1,8,0,0,6,
		0,0,0,6,0,0,9,0,0,
		7,6,0,0,4,0,0,2,1,
		6,0,0,0,3,4,0,0,9,
		0,0,7,0,8,9,1,0,3,
		9,0,2,0,7,0,0,0,0
		};
	SudokuGame sg;
	sg.set(game);
	sg.write("easy.sudokugame");
	checkEqual( sg.getCell(1,0).getValue() , 3 );
	checkEqual( sg.getCell(2,2).getValue() , 8 );
	checkEqual( sg.getCell(8,4).getValue() , 7 );
	checkEqual( sg.getCell(2,5).getNumberOfPossibleValues() , 3 );
	checkEqual( sg.getCell(5,2).getNumberOfPossibleValues() , 2 );
}

TestCase( CreateGameFromMatrix )
{
	vector< vector<unsigned> > game = {
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
	sg.set(game);
	sg.write("easy.sudokugame");
	checkEqual( sg.getCell(1,0).getValue() , 3 );
	checkEqual( sg.getCell(2,2).getValue() , 8 );
	checkEqual( sg.getCell(8,4).getValue() , 7 );
	checkEqual( sg.getCell(2,5).getNumberOfPossibleValues() , 3 );
	checkEqual( sg.getCell(5,2).getNumberOfPossibleValues() , 2 );
}

TestCase( SolveSudokuGameUsingOnePossibleValueStrategy )
{
	unsigned problem[] = {
		0,0,0,2,6,0,7,0,1,
		6,8,0,0,7,0,0,9,0,
		1,9,0,0,0,4,5,0,0,
		8,2,0,1,0,0,0,4,0,
		0,0,4,6,0,2,9,0,0,
		0,5,0,0,0,3,0,2,8,
		0,0,9,3,0,0,0,7,4,
		0,4,0,0,5,0,0,3,6,
		7,0,3,0,1,8,0,0,0
		};
	SudokuGame sgProblem;
	sgProblem.set(problem);
	sgProblem.write("easy_unsolved.sudokugame");
	check( sgProblem.isValid() );
	sgProblem.solverForOnePossibleValue();
	sgProblem.write("easy_solved.sudokugame");
	check( sgProblem.isValid() );

	unsigned solution[] = {
		4,3,5,2,6,9,7,8,1,
		6,8,2,5,7,1,4,9,3,
		1,9,7,8,3,4,5,6,2,
		8,2,6,1,9,5,3,4,7,
		3,7,4,6,8,2,9,1,5,
		9,5,1,7,4,3,6,2,8,
		5,1,9,3,2,6,8,7,4,
		2,4,8,9,5,7,1,3,6,
		7,6,3,4,1,8,2,5,9
		};
	SudokuGame sgSolution;
	sgSolution.set(solution);
	check( sgSolution.isValid() );
	sgSolution.write("solution.sudokugame");

	check( sgProblem == sgSolution );
}
