#define BOOST_TEST_MODULE TestModule

#include <vector>

#include <Test.h>
#include <PossibleValues.h>

#include <Cell.h>
#include <Group.h>
#include <Row.h>
#include <Column.h>
#include <Rectangle.h>
#include <SudokuGame.h>

#include <AppFunctions.h>

TestCase( check_is_valid_sudoku_game )
{
	const char * fileName = "is_game_valid_test.sudokugame";
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
	sg.createFile(fileName,"Problem");
	check( checkIsValidSudokuGame(fileName,"Problem") );
}

TestCase( check_is_solved_sudoku_game )
{
	const char * fileName = "is_game_solved_test.sudokugame";
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
	sg.solveForOnePossibleValue();
	sg.createFile(fileName,"Problem");
	check( checkIsSolvedSudokuGame(fileName,"Problem") );
}
