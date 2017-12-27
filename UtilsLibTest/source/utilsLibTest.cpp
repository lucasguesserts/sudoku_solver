#define BOOST_TEST_MODULE TestModule

// std
//#include <iostream>
//using std::cout;
//using std::endl;
#include <vector>
using std::vector;

// Utils
#include <Test.h>
#include <Foreach.h>
#include <PossibleValues.h>
#include <Position.h>

TestCase( CheckEqualAndCheckClose )
{
	double i = 0;
	double j = 0;

	checkClose( i , j , 1.0e-12 );
	checkEqual( i , j );
}

TestCase( ForeachTest ){
	vector<double> values;
	int nValues = 5;
	double rawValues[] = { 2.71, 3.14, 0.0, -3.14, -2.71 };

	for( int i = 0; i < nValues; ++i ){
		values.push_back( rawValues[ i ] );
	}

	int counter = 0;
	foreach( double v, values ){
		checkClose( rawValues[ counter ], v, 1.0e-12 );
		++counter; 
	}
}

TestCase( InsertTest )
{
	PossibleValues pvInsert;

	unsigned start	= 0;
	unsigned end	= 20;

	for(unsigned i=start ; i<(end+1) ; ++i)
	{
		pvInsert.insert(i);
	}

	checkEqual( pvInsert.size() , (end-start+1) );
}

TestCase( PossibleValuesCopyConstructor )
{
	PossibleValues pv(allPossibleValues);

	check( pv == allPossibleValues );
}

TestCase( PossibleValuesIsEqualOperator )
{
	unsigned insertValues[] = {1 , 5 , 34};
	PossibleValues pv0(insertValues , insertValues+3);
	PossibleValues pv1(insertValues , insertValues+3);

	check( pv0 == pv1 );
}

TestCase( PossibleValuesIsDifferentOperator )
{
	unsigned insertValues[] = {1 , 5 , 34};
	PossibleValues pv0(insertValues , insertValues+3);
	PossibleValues pv1(insertValues , insertValues+3);
	PossibleValues pv2(insertValues , insertValues+2);

	checkEqual( pv0 != pv1 , false );
	checkEqual( pv0 != pv2 , true );
}

TestCase( FirstAndLastValues )
{
	unsigned firstValue	= FIRST_VALUE;
	unsigned lastValue	= N_VALUES;

	checkEqual( firstPossibleValue , firstValue );
	checkEqual( lastPossibleValue , lastValue );
}

TestCase( AllPossibleValues )
{

	checkEqual(firstPossibleValue , 1);
	checkEqual(lastPossibleValue , 9);

	PossibleValues pv;
	for(unsigned i=firstPossibleValue ; i<(lastPossibleValue+1) ; ++i)
	{
		pv.insert(i);
	}

	check( allPossibleValues == pv );
}

TestCase( VoidSet )
{
	PossibleValues pv;
	checkEqual( pv.empty() , true );
}

TestCase( RemoveSetElement )
{
	PossibleValues pv;

	for(unsigned i=1 ; i<10 ; ++i)
	{
		pv.insert(i);
	}

	unsigned toErase = 4;
	pv.erase(toErase);

	// do not works
	//checkEqual( pv.find(toErase) , pv.end() );

	check( pv.find(toErase)==pv.end() );
	checkEqual( pv.count(toErase) , 0 );
}

TestCase( EraseSet )
{
	PossibleValues pv;

	for(unsigned i=1 ; i<10 ; ++i)
	{
		pv.insert(i);
	}

	checkEqual( pv.count(1) , 1 );

	pv.clear();
	checkEqual( pv.size() , 0 );
}

TestCase( PositionDefaultConstructor )
{
	Position pos;

	checkEqual( pos.row , 0 );
	checkEqual( pos.column , 0 );
}

TestCase( PositionConstructor )
{
	Position pos(3,4);

	checkEqual( pos.row , 3 );
	checkEqual( pos.column , 4 );
}

TestCase( PositionSet )
{
	Position pos;
	pos.set(3,4);

	checkEqual( pos.row , 3 );
	checkEqual( pos.column , 4 );
}

TestCase( PositionCopy )
{
	Position pos1(1,2);
	Position pos2 = pos1;
	checkEqual( pos1.row , pos2.row );
	checkEqual( pos1.column , pos2.column );
}
