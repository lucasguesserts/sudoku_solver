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

TestCase( "cell_void_constructor", "[cell]" )
{
	Cell c;
	const unsigned defaultValue = 0;
	const unsigned numberOfPossibleValues = 9;
	check( c.getValue() == defaultValue );
	check( c.getNumberOfPossibleValues() == numberOfPossibleValues );
}

TestCase( "cell_setValue_and_getValue", "[cell]" )
{
	unsigned value = 6;
	Cell cell;
	cell.setValue(value);
	check(cell.getValue() == value);
	check(cell.getNumberOfPossibleValues() == 0);
}

TestCase( "cell_setValue_zero", "[cell]" )
{
	Cell cell;
	cell.setValue(0);
	check( cell.getNumberOfPossibleValues() == PossibleValues::numberOfValues );
}

TestCase( "erase_possible_value", "[cell]" )
{
	Cell cell;
	std::vector<unsigned> valuesToBeErased = {1,2,3,4,5,6,7,8,9};
	for( unsigned value : valuesToBeErased )
		cell.erasePossibleValue(value);
	check( cell.getNumberOfPossibleValues() == 0 );
}

TestCase( "cell_unique_possible_value", "[cell]" )
{
	Cell cell;
	std::vector<unsigned> valuesToBeErased = {1,2,3,4,6,7,8,9};
	unsigned uniqueValue = 5;
	for( unsigned value : valuesToBeErased )
		cell.erasePossibleValue(value);
	check( cell.getNumberOfPossibleValues() == 1 );
	check( cell.getUniquePossibleValue() == uniqueValue );
}

TestCase( "cell_addToGroup_and_getGroups", "[cell]" )
{
	Cell cell;
	Group group[5];
	for (unsigned i=0 ; i<5 ; ++i)
		cell.addToGroup(group[i]);
	std::vector<Group *> cellGroups = cell.getGroups();
	for (unsigned i=0 ; i<5 ; ++i)
		check(&group[i] == cellGroups[i]);
}

TestCase( "cell_isValid_false", "[cell]" )
{
	const unsigned value = 3;
	Cell cell[2];
	Group group;
	group.addCell(cell[0]);
	group.addCell(cell[1]);
	cell[0].setValue(value);
	cell[1].setValue(value);
	checkFalse( cell[0].isValid() );
}

TestCase( "cell_isValid_true", "[cell]" )
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

TestCase( "group_addCell_and_getCells", "[group]" )
{
	Cell cell[5];
	Group group;
	for (unsigned i=0 ; i<5 ; ++i)
		group.addCell(cell[i]);
	std::vector<Cell *> cellsInGroup = group.getCells();
	for (unsigned i=0 ; i<5 ; ++i)
		check(&cell[i] == cellsInGroup[i]);
}

TestCase( "group_isValid_true", "[group]" )
{
	const unsigned size = PossibleValues::numberOfValues; 
	std::vector<unsigned> values = {1,2,3,4,5,6,7,8,9};
	std::vector<Cell> cell(size);
	Group group;
	for(unsigned i=0 ; i<size ; ++i)
		group.addCell(cell[i]);
	for(unsigned i=0 ; i<size ; ++i)
		cell[i].setValue(values[i]);
	check( group.isValid() );
}

TestCase( "group_isValid_false", "[group]" )
{
	const unsigned value = 5;
	Cell cell[2];
	Group group;
	group.addCell(cell[0]);
	group.addCell(cell[1]);
	cell[0].setValue(value);
	cell[1].setValue(value);
	checkFalse( group.isValid() );
}

//// ############### SudokuGame ###############

TestCase( "SudokuGame_getValue", "[sudoku game]" )
{
	unsigned row = 2;
	unsigned column = 5;
	unsigned defaultValue = 0;
	SudokuGame sg;
	check( sg.getCellValue(row,column) == defaultValue );
}

TestCase( "SudokuGame_getNumberOfPossibleValues", "[sudoku game]" )
{
	unsigned row = 2;
	unsigned column = 5;
	unsigned value = 8;
	SudokuGame sg;
	check( sg.getCellValue(row,column) == 0 );
	check( sg.getCellNumberOfPossibleValues(row,column) == PossibleValues::numberOfValues );
	sg.setCellValue(row,column,value);
	check( sg.getCellValue(row,column) == value );
	check( sg.getCellNumberOfPossibleValues(row,column) == 0 );
}

TestCase( "SudouGame_setCellValue", "[sudoku game]" )
{
	SudokuGame sg;
	const unsigned r = 3;
	const unsigned c = 4;
	const unsigned value = 2;
	sg.setCellValue(r,c,value);
	check( sg.getCellValue(r,c) == value );
	for( unsigned row=0 ; row<SudokuGame::size ; ++row)
	{
		if (row==r) continue;
		check( sg.getCellNumberOfPossibleValues(row,c) == PossibleValues::numberOfValues-1);
	}
	for( unsigned column=0 ; column<SudokuGame::size ; ++column)
	{
		if (column==c) continue;
		check( sg.getCellNumberOfPossibleValues(r,column) == PossibleValues::numberOfValues-1);
	}
	// rectangle 1x0
	for(unsigned row=3 ; row<6 ; ++row)
	{
		for(unsigned column=3 ; column<6 ; ++column)
		{
			if (row==r && column==c) continue;
			check( sg.getCellNumberOfPossibleValues(row,column) == PossibleValues::numberOfValues-1);
		}
	}
}

TestCase( "SudokuGame_getCellUniquePossibleValue", "[sudoku game]" )
{
	SudokuGame sg;
	const unsigned r = 2;
	unsigned c;
	for(c=0 ; c<(SudokuGame::size-1) ; ++c)
	{
		sg.setCellValue(r , c , c+1);
	}
	c = 8;
	check( sg.getCellUniquePossibleValue(r,c) == PossibleValues::lastValue );
}

TestCase( "SudokuGame_voidGame_isValid", "[sudoku game]" ) 
{
	SudokuGame sg;
	check( sg.isValid() );
}

TestCase( "SudokuGame_example", "[sudoku game]" ) 
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
	SudokuGame sg;
	sg.set(game);
	sg.createFile(fileName,datasetName);
	sg.appendInFile(fileName,voidDatasetName);
	section( "set_using_matrix" )
	{
		check( sg.getCellValue(1,0) == 3 );
		check( sg.getCellValue(2,2) == 8 );
		check( sg.getCellValue(8,4) == 7 );
		check( sg.getCellNumberOfPossibleValues(2,5) == 3 );
		check( sg.getCellNumberOfPossibleValues(5,2) == 2 );
	}
	section( "isValid_true" )
	{
		check( sg.isValid() );
	}
	section( "isValid_false" )
	{
		unsigned row = 0;
		unsigned column;
		unsigned value = 1;
		column = 0; sg.setCellValue(row,column,value);
		column = 1; sg.setCellValue(row,column,value);
		checkFalse( sg.isValid() );
	}
	section( "isSolved_false" )
	{
		checkFalse( sg.isSolved() );
	}
	section( "solveForOnePossibleValue" )
	{
		sg.solveForOnePossibleValue();
		check( sg.isSolved() );
	}
	section( "create_read_file" )
	{
		SudokuGame sg2;
		sg2.readFromFile(fileName,datasetName);
		check( sg2.getCellValue(1,0) == 3 );
		check( sg2.getCellValue(2,2) == 8 );
		check( sg2.getCellValue(8,4) == 7 );
		check( sg2.getCellNumberOfPossibleValues(2,5) == 3 );
		check( sg2.getCellNumberOfPossibleValues(5,2) == 2 );
	}
	section( "appendInFile" )
	{
		SudokuGame sg3;
		sg3.readFromFile(fileName,voidDatasetName);
		check( sg3.getCellValue(1,0) == 3 );
		check( sg3.getCellValue(2,2) == 8 );
		check( sg3.getCellValue(8,4) == 7 );
		check( sg3.getCellNumberOfPossibleValues(2,5) == 3 );
		check( sg3.getCellNumberOfPossibleValues(5,2) == 2 );
	}
}

TestCase( "SudokuGame_isSolved", "[sudoku game]" )
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

