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
	foreach( unsigned value , valuesToBeErased )
		cell.erasePossibleValue(value);
	checkEqual( cell.getNumberOfPossibleValues() , 0 );
}

TestCase( cell_unique_possible_value )
{
	Cell cell;
	std::vector<unsigned> valuesToBeErased = {1,2,3,4,6,7,8,9};
	unsigned uniqueValue = 5;
	foreach( unsigned value , valuesToBeErased )
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

//TestCase( GroupGetNumberOfCells )
//{
	//Cell c0, c1, c2;
	//Group g;
	//g.addCell(c0);
	//g.addCell(c1);
	//g.addCell(c2);
	//checkEqual( g.getNumberOfCell() , 3 );
//}

//TestCase( GroupGetCellValue )
//{
	//const unsigned value = 8;
	//Group g;
	//Cell c;
	//g.addCell(c);
	//c.setValue(value);
	//checkEqual( g.getCellValue(0) , value );
//}

//// ############### SudokuGame ###############

//TestCase( SudokuGameGetCellNumberOfPossibleValues )
//{
	//SudokuGame sg;
	//const unsigned r=2 , c=3;
	//const unsigned defaultSize = allPossibleValues.size();
	//checkEqual( sg.getCellNumberOfPossibleValues(r,c) , defaultSize );
//}

//TestCase( SudouGameSetCellValue )
//{
	//SudokuGame sg;
	//const unsigned r = 3; const unsigned rectangleRow = 1;
	//const unsigned c = 4; const unsigned rectangleColumn = 1;
	//const unsigned value = 2;

	//sg.setCellValue(r , c , value);
	//checkEqual( sg.getCell(r,c).getValue() , value );

	//foreach( Cell * cell , sg.getRow(r).getCells() )
	//{
		//checkEqual( cell->havePossibleValue(value) , false);
	//}

	//foreach( Cell * cell , sg.getColumn(c).getCells() )
	//{
		//checkEqual( cell->havePossibleValue(value) , false);
	//}

	//foreach( Cell * cell , sg.getRectangle(rectangleRow , rectangleColumn).getCells() )
	//{
		//checkEqual( cell->havePossibleValue(value) , false);
	//}
//}

//TestCase( SudokuGameGetCellUniquePossibleValue )
//{
	//SudokuGame sg;
	//const unsigned r = 2;
	//for(unsigned c=0 ; c<(N_VALUES-1) ; ++c)
	//{
		//sg.setCellValue(r , c , c+1);
	//}
	//checkEqual( sg.getCellUniquePossibleValue(r,8) , N_VALUES );
//}

//TestCase( SudokuGameSetCellValue )
//{
	//const unsigned r = 3;
	//const unsigned c = 2;
	//const unsigned value = 1;
	//SudokuGame sg;
	//Row row = sg.getRow(r);
	//Column column = sg.getColumn(c);
	//sg.setCellValue(r,c,value);
	//checkEqual(row.getCellValue(c) , value);
	//checkEqual(column.getCellValue(r) , value);
//}

//// Refactoring needed!!!!!!!!!!!!!!!!!!!!!!!
//TestCase( WriteSudokuGame )
//{
	//SudokuGame sg1, sg2;
	//sg1.setCellValue(2,3,5);
	//sg1.write("empty_sudoku_game.sudokugame");
	//sg2.read("empty_sudoku_game.sudokugame");
	//checkEqual( sg2.getCell(2,3).getValue() , 5 );
//}

//TestCase( CreateGameFromArray )
//{
	//unsigned game[] = {
		//0,0,4,0,6,0,0,5,8,
		//3,0,0,8,9,0,0,1,7,
		//1,0,8,0,0,0,0,0,2,
		//0,2,5,0,1,8,0,0,6,
		//0,0,0,6,0,0,9,0,0,
		//7,6,0,0,4,0,0,2,1,
		//6,0,0,0,3,4,0,0,9,
		//0,0,7,0,8,9,1,0,3,
		//9,0,2,0,7,0,0,0,0
		//};
	//SudokuGame sg;
	//sg.set(game);
	//sg.write("easy.sudokugame");
	//checkEqual( sg.getCell(1,0).getValue() , 3 );
	//checkEqual( sg.getCell(2,2).getValue() , 8 );
	//checkEqual( sg.getCell(8,4).getValue() , 7 );
	//checkEqual( sg.getCell(2,5).getNumberOfPossibleValues() , 3 );
	//checkEqual( sg.getCell(5,2).getNumberOfPossibleValues() , 2 );
//}

//TestCase( CreateGameFromVector )
//{
	//vector<unsigned> game = {
		//0,0,4,0,6,0,0,5,8,
		//3,0,0,8,9,0,0,1,7,
		//1,0,8,0,0,0,0,0,2,
		//0,2,5,0,1,8,0,0,6,
		//0,0,0,6,0,0,9,0,0,
		//7,6,0,0,4,0,0,2,1,
		//6,0,0,0,3,4,0,0,9,
		//0,0,7,0,8,9,1,0,3,
		//9,0,2,0,7,0,0,0,0
		//};
	//SudokuGame sg;
	//sg.set(game);
	//sg.write("easy.sudokugame");
	//checkEqual( sg.getCell(1,0).getValue() , 3 );
	//checkEqual( sg.getCell(2,2).getValue() , 8 );
	//checkEqual( sg.getCell(8,4).getValue() , 7 );
	//checkEqual( sg.getCell(2,5).getNumberOfPossibleValues() , 3 );
	//checkEqual( sg.getCell(5,2).getNumberOfPossibleValues() , 2 );
//}

//TestCase( CreateGameFromMatrix )
//{
	//vector< vector<unsigned> > game = {
		//{0,0,4,0,6,0,0,5,8},
		//{3,0,0,8,9,0,0,1,7},
		//{1,0,8,0,0,0,0,0,2},
		//{0,2,5,0,1,8,0,0,6},
		//{0,0,0,6,0,0,9,0,0},
		//{7,6,0,0,4,0,0,2,1},
		//{6,0,0,0,3,4,0,0,9},
		//{0,0,7,0,8,9,1,0,3},
		//{9,0,2,0,7,0,0,0,0}
		//};
	//SudokuGame sg;
	//sg.set(game);
	//sg.write("easy.sudokugame");
	//checkEqual( sg.getCell(1,0).getValue() , 3 );
	//checkEqual( sg.getCell(2,2).getValue() , 8 );
	//checkEqual( sg.getCell(8,4).getValue() , 7 );
	//checkEqual( sg.getCell(2,5).getNumberOfPossibleValues() , 3 );
	//checkEqual( sg.getCell(5,2).getNumberOfPossibleValues() , 2 );
//}

//TestCase( SolveSudokuGameUsingOnePossibleValueStrategy )
//{
	//vector<unsigned> problem = {
		//0,0,0,2,6,0,7,0,1,
		//6,8,0,0,7,0,0,9,0,
		//1,9,0,0,0,4,5,0,0,
		//8,2,0,1,0,0,0,4,0,
		//0,0,4,6,0,2,9,0,0,
		//0,5,0,0,0,3,0,2,8,
		//0,0,9,3,0,0,0,7,4,
		//0,4,0,0,5,0,0,3,6,
		//7,0,3,0,1,8,0,0,0
		//};
	//SudokuGame sgProblem;
	//sgProblem.set(problem);
	//sgProblem.write("easy_unsolved.sudokugame");
	//check( sgProblem.isValid() );
	//sgProblem.solverForOnePossibleValue();
	//sgProblem.write("easy_solved.sudokugame");
	//check( sgProblem.isValid() );

	//vector<unsigned> solution = {
		//4,3,5,2,6,9,7,8,1,
		//6,8,2,5,7,1,4,9,3,
		//1,9,7,8,3,4,5,6,2,
		//8,2,6,1,9,5,3,4,7,
		//3,7,4,6,8,2,9,1,5,
		//9,5,1,7,4,3,6,2,8,
		//5,1,9,3,2,6,8,7,4,
		//2,4,8,9,5,7,1,3,6,
		//7,6,3,4,1,8,2,5,9
		//};
	//SudokuGame sgSolution;
	//sgSolution.set(solution);
	//check( sgSolution.isValid() );
	//sgSolution.write("solution.sudokugame");

	//check( sgProblem == sgSolution );
//}
