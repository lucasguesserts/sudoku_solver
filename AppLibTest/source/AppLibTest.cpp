#include <vector>
#include <cstring>

#include <Test.h>
#include <PossibleValues.h>

#include <Cell.h>
#include <Group.h>
#include <Row.h>
#include <Column.h>
#include <Rectangle.h>
#include <SudokuGame.h>

#include <AppFunctions.h>

TestCase( "create_empty_sudoku_game", "[app]" )
{
	const char * fileName = "empty_sudoku_game_test";
	const char * fileNameWithExtension = "empty_sudoku_game_test.sudokugame";
	SudokuGame sg;
	createEmptySudokuGame(fileName);
	sg.readFromFile(fileNameWithExtension,AppDefinition::problemDatasetName);
	for(unsigned row=0 ; row<SudokuGame::size ; ++row)
		for(unsigned column=0 ; column<SudokuGame::size ; ++column)
			check( sg.getCellValue(row,column) == 0 );
}

TestCase( "sudoku game example", "[app]" )
{
	const char * fileName = "appLib_example.sudokugame";
	SudokuGame sg;
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
	sg.set(game);
	sg.createFile(fileName,AppDefinition::problemDatasetName);
	section( "check is valid" )
	{
		check( checkIsValidSudokuGame(fileName,AppDefinition::problemDatasetName) );
	}
	section( "check is solved" )
	{
		sg.solveForOnePossibleValue();
		sg.appendInFile(fileName,AppDefinition::solutionDatasetName);
		check( checkIsSolvedSudokuGame(fileName,AppDefinition::solutionDatasetName) );
	}
	section( "solve game" )
	{
		std::vector< std::vector<unsigned> > solved_game = {
			{2,9,4,7,6,1,3,5,8},
			{3,5,6,8,9,2,4,1,7},
			{1,7,8,4,5,3,6,9,2},
			{4,2,5,9,1,8,7,3,6},
			{8,1,3,6,2,7,9,4,5},
			{7,6,9,3,4,5,8,2,1},
			{6,8,1,5,3,4,2,7,9},
			{5,4,7,2,8,9,1,6,3},
			{9,3,2,1,7,6,5,8,4}
		};
		SudokuGame sg_solved, sg_solved_read;
		sg_solved.set(solved_game);
		check( solveSudokuGame(fileName,AppDefinition::problemDatasetName) );
		sg_solved_read.readFromFile(fileName,AppDefinition::solutionDatasetName);
		check( sg_solved == sg_solved_read );
	}
}

TestCase( "select app behaviour", "[app]" )
{
	char behaviour[200];

	strcpy(behaviour,"create_empty");
	check( AppBehaviour::create_empty == selectBehaviour(behaviour) );

	strcpy(behaviour,"check");
	check( AppBehaviour::check == selectBehaviour(behaviour) );

	strcpy(behaviour,"solved");
	check( AppBehaviour::solved == selectBehaviour(behaviour) );

	strcpy(behaviour,"solve");
	check( AppBehaviour::solve == selectBehaviour(behaviour) );

	strcpy(behaviour,"something invalid");
	check( AppBehaviour::error == selectBehaviour(behaviour) );
}

TestCase( "verify number of inputs", "[app]" )
{
	int argc;
	argc = 2;
	checkFalse( checkNumberOfInputs(argc) );
	argc = 3;
	check( checkNumberOfInputs(argc) );
}
