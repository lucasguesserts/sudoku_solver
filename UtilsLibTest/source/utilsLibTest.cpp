#define BOOST_TEST_MODULE TestModule

// Utils
#include <Test.h>
#include <PossibleValues.h>

TestCase( CheckEqualAndCheckClose )
{
	double i = 0;
	double j = 0;

	checkClose( i , j , 1.0e-12 );
	checkEqual( i , j );
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

TestCase( FirstAndLastValues )
{
	unsigned firstValue	= FIRST_VALUE;
	unsigned lastValue	= N_VALUES;

	checkEqual( firstPossibleValue , firstValue );
	checkEqual( lastPossibleValue , lastValue );
}

TestCase( AllPossibleValues )
{
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
