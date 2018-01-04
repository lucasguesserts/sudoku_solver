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


// ############### Cell ###############

TestCase( cell_void_constructor )
{
	Cell c;
	const unsigned defaultValue = 0;
	const unsigned numberOfPossibleValues = 9;
	checkEqual( c.getValue() , defaultValue );
	checkEqual( c.getNumberOfPossibleValues() , numberOfPossibleValues );
}
