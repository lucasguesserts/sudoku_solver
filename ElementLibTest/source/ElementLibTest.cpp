#define BOOST_TEST_MODULE TestModule

#include <vector>

#include <Cell.h>
#include <Group.h>
#include <Row.h>
#include <Column.h>
#include <Rectangle.h>
#include <SudokuGame.h>

#include <Test.h>
#include <PossibleValues.h>


// ############### Cell ###############

TestCase( cell_void_constructor )
{
	Cell c;
	const unsigned defaultValue = 0;
	const unsigned numberOfPossibleValues = 9;
	checkEqual( c.getValue() , defaultValue );
	checkEqual( c.getNumberOfPossibleValues() , numberOfPossibleValues );
}

TestCase( cell_setValue_and_getValue )
{
	unsigned value = 6;
	Cell cell;
	cell.setValue(value);
	checkEqual(cell.getValue() , value);
	checkEqual(cell.getNumberOfPossibleValues() , 0);
}

TestCase( cell_setValue_zero )
{
	Cell cell;
	const unsigned numberOfPossibleValues = 9;
	cell.setValue(0);
	checkEqual( cell.getNumberOfPossibleValues() , numberOfPossibleValues );
}

TestCase( erase_possible_value )
{
	Cell cell;
	std::vector<unsigned> valuesToBeErased = {1,2,3,4,5,6,7,8,9};
	for( unsigned value : valuesToBeErased )
		cell.erasePossibleValue(value);
	checkEqual( cell.getNumberOfPossibleValues() , 0 );
}

TestCase( cell_unique_possible_value )
{
	Cell cell;
	std::vector<unsigned> valuesToBeErased = {1,2,3,4,6,7,8,9};
	unsigned uniqueValue = 5;
	for( unsigned value : valuesToBeErased )
		cell.erasePossibleValue(value);
	checkEqual( cell.getNumberOfPossibleValues() , 1 );
	checkEqual( cell.getUniquePossibleValue() , uniqueValue );
}

TestCase( cell_addToGroup_and_getGroups )
{
	Cell cell;
	Group group[5];
	for (unsigned i=0 ; i<5 ; ++i)
		cell.addToGroup(group[i]);
	std::vector<Group *> cellGroups = cell.getGroups();
	for (unsigned i=0 ; i<5 ; ++i)
		checkEqual(&group[i] , cellGroups[i]);
}

TestCase( cell_isValid_false )
{
	const unsigned value = 3;
	Cell cell[2];
	Group group;
	group.addCell(cell[0]);
	group.addCell(cell[1]);
	cell[0].setValue(value);
	cell[1].setValue(value);
	checkEqual( cell[0].isValid() , false );
}

TestCase( cell_isValid_true )
{
	const unsigned value[3] = {0,5,6};
	Cell cell[3];
	Group group;
	group.addCell(cell[0]);
	group.addCell(cell[1]);
	group.addCell(cell[2]);
	cell[0].setValue(value[0]);
	cell[1].setValue(value[1]);
	cell[2].setValue(value[2]);
	check( cell[0].isValid() );
	check( cell[0].isValid() );
	check( cell[0].isValid() );
}

// ############### Group ###############

TestCase( group_addCell_and_getCells )
{
	Cell cell[5];
	Group group;
	for (unsigned i=0 ; i<5 ; ++i)
		group.addCell(cell[i]);
	std::vector<Cell *> cellsInGroup = group.getCells();
	for (unsigned i=0 ; i<5 ; ++i)
		checkEqual(&cell[i] , cellsInGroup[i]);
}

TestCase( group_isValid_true )
{
	const unsigned size = PossibleValues::lastValue; 
	std::vector<unsigned> values = {1,2,3,4,5,6,7,8,9};
	std::vector<Cell> cell(size);
	Group group;
	for(unsigned i=0 ; i<size ; ++i)
		group.addCell(cell[i]);
	for(unsigned i=0 ; i<size ; ++i)
		cell[i].setValue(values[i]);
	check( group.isValid() );
}

TestCase( group_isValid_false )
{
	const unsigned value = 5;
	Cell cell[2];
	Group group;
	group.addCell(cell[0]);
	group.addCell(cell[1]);
	cell[0].setValue(value);
	cell[1].setValue(value);
	checkEqual( group.isValid() , false );
}

//// ############### SudokuGame ###############

TestCase( SudokuGame_getValue )
{
	unsigned row = 2;
	unsigned column = 5;
	unsigned defaultValue = 0;
	SudokuGame sg;
	checkEqual( sg.getCellValue(row,column), defaultValue );
}

TestCase( SudokuGame_getNumberOfPossibleValues )
{
	unsigned row = 2;
	unsigned column = 5;
	unsigned value = 8;
	SudokuGame sg;
	checkEqual( sg.getCellValue(row,column), 0 );
	checkEqual( sg.getCellNumberOfPossibleValues(row,column) , PossibleValues::numberOfValues );
	sg.setCellValue(row,column,value);
	checkEqual( sg.getCellValue(row,column), value );
	checkEqual( sg.getCellNumberOfPossibleValues(row,column) , 0 );
}

TestCase( SudouGame_setCellValue )
{
	SudokuGame sg;
	const unsigned r = 3;
	const unsigned c = 4;
	const unsigned value = 2;
	sg.setCellValue(r,c,value);
	checkEqual( sg.getCellValue(r,c) , value );
	for( unsigned row=0 ; row<SudokuGame::size ; ++row)
	{
		if (row==r) continue;
		checkEqual( sg.getCellNumberOfPossibleValues(row,c) , PossibleValues::numberOfValues-1);
	}
	for( unsigned column=0 ; column<SudokuGame::size ; ++column)
	{
		if (column==c) continue;
		checkEqual( sg.getCellNumberOfPossibleValues(r,column) , PossibleValues::numberOfValues-1);
	}
	// rectangle 1x0
	for(unsigned row=3 ; row<6 ; ++row)
		for(unsigned column=3 ; column<6 ; ++column)
		{
			if (row==r && column==c) continue;
			checkEqual( sg.getCellNumberOfPossibleValues(row,column) , PossibleValues::numberOfValues-1);
		}
}

TestCase( SudokuGame_getCellUniquePossibleValue )
{
	SudokuGame sg;
	const unsigned r = 2;
	unsigned c;
	for(c=0 ; c<(SudokuGame::size-1) ; ++c)
	{
		sg.setCellValue(r , c , c+1);
	}
	c = 8;
	checkEqual( sg.getCellUniquePossibleValue(r,c) , PossibleValues::lastValue );
}

TestCase( SudokuGame_set_using_matrix )
{
	std::vector< std::vector<unsigned> > game = {
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
	checkEqual( sg.getCellValue(1,0) , 3 );
	checkEqual( sg.getCellValue(2,2) , 8 );
	checkEqual( sg.getCellValue(8,4) , 7 );
	checkEqual( sg.getCellNumberOfPossibleValues(2,5) , 3 );
	checkEqual( sg.getCellNumberOfPossibleValues(5,2) , 2 );
}

TestCase( SudokuGame_isValid )
{
	SudokuGame sg;
	check( sg.isValid() );
}

TestCase( SudokuGame_isValid_true )
{
	std::vector< std::vector<unsigned> > game = {
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
	check( sg.isValid() );
}

TestCase( SudokuGame_isValid_false )
{
	std::vector< std::vector<unsigned> > game = {
		{1,1,4,0,6,0,0,5,8},
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
	check( ! sg.isValid() );
}

TestCase( SudokuGame_isSolved_true )
{
	std::vector< std::vector<unsigned> > solved_game = {
		{4,3,5,2,6,9,7,8,1},
		{6,8,2,5,7,1,4,9,3},
		{1,9,7,8,3,4,5,6,2},
		{8,2,6,1,9,5,3,4,7},
		{3,7,4,6,8,2,9,1,5},
		{9,5,1,7,4,3,6,2,8},
		{5,1,9,3,2,6,8,7,4},
		{2,4,8,9,5,7,1,3,6},
		{7,6,3,4,1,8,2,5,9}
		};
	SudokuGame sg;
	sg.set(solved_game);
	check( sg.isSolved() );
}

TestCase( SudokuGame_isSolved_false )
{
	std::vector< std::vector<unsigned> > solved_game = {
		{0,3,5,2,6,9,7,8,1},
		{6,8,2,5,7,1,4,9,3},
		{1,9,7,8,3,4,5,6,2},
		{8,2,6,1,9,5,3,4,7},
		{3,7,4,6,8,2,9,1,5},
		{9,5,1,7,4,3,6,2,8},
		{5,1,9,3,2,6,8,7,4},
		{2,4,8,9,5,7,1,3,6},
		{7,6,3,4,1,8,2,5,9}
		};
	SudokuGame sg;
	sg.set(solved_game);
	check( ! sg.isSolved() );
}

TestCase( SudokuGame_solveForOnePossibleValue )
{
	std::vector< std::vector<unsigned> > game = {
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
	sg.solveForOnePossibleValue();
	check( sg.isSolved() );
}

TestCase( SudokuGame_create_read_file )
{
	const char * fileName = "create_read_test.sudokugame";
	const char * datasetName = "problem";
	std::vector< std::vector<unsigned> > game = {
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
	SudokuGame sg[2];
	sg[0].set(game);
	sg[0].createFile(fileName,datasetName);
	sg[1].readFromFile(fileName,datasetName);
	checkEqual( sg[1].getCellValue(1,0) , 3 );
	checkEqual( sg[1].getCellValue(2,2) , 8 );
	checkEqual( sg[1].getCellValue(8,4) , 7 );
	checkEqual( sg[1].getCellNumberOfPossibleValues(2,5) , 3 );
	checkEqual( sg[1].getCellNumberOfPossibleValues(5,2) , 2 );
}

TestCase( SudokuGame_appendInFile )
{
	const char * fileName = "appendInFile_test.sudokugame";
	const char * voidDatasetName = "void_game";
	const char * datasetName = "problem";
	std::vector< std::vector<unsigned> > game = {
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
	SudokuGame sg[3];
	sg[0].createFile(fileName,voidDatasetName);
	sg[1].set(game);
	sg[1].appendInFile(fileName,datasetName);
	sg[2].readFromFile(fileName,datasetName);
	checkEqual( sg[2].getCellValue(1,0) , 3 );
	checkEqual( sg[2].getCellValue(2,2) , 8 );
	checkEqual( sg[2].getCellValue(8,4) , 7 );
	checkEqual( sg[2].getCellNumberOfPossibleValues(2,5) , 3 );
	checkEqual( sg[2].getCellNumberOfPossibleValues(5,2) , 2 );
}
