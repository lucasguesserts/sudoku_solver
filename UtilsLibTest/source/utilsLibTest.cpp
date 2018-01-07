#define CATCH_CONFIG_MAIN
#include <catch.hpp>

TEST_CASE( "catch test" )
{
	int a,b;
	a = 3;
	b = 3;
	CHECK( a==b );
	a = 4;
	b = 5;
	CHECK( a==b);
}
//#define BOOST_TEST_MODULE TestModule

//#include <vector>

//#include <Test.h>
//#include <PossibleValues.h>

//TestCase( CheckEqualAndCheckClose )
//{
	//double i = 0;
	//double j = 0;

	//checkClose( i , j , 1.0e-12 );
	//checkEqual( i , j );
//}

//TestCase( cpp_11_foreach ){
	//std::vector<double> values;
	//int nValues = 5;
	//double rawValues[] = { 2.71, 3.14, 0.0, -3.14, -2.71 };

	//for( int i = 0; i < nValues; ++i ){
		//values.push_back( rawValues[ i ] );
	//}

	//int counter = 0;
	//for( double v: values ){
		//checkClose( rawValues[ counter ], v, 1.0e-12 );
		//++counter; 
	//}
//}

//TestCase( PossibleValuesConstructor )
//{
	//std::set<unsigned> testSet;
	//std::vector<unsigned> setValues = {1,2,3,4,5,6,7,8,9};
	//for(unsigned value : setValues)
		//testSet.insert(value);
	//check(static_cast< std::set<unsigned> >(PossibleValues()) == testSet);
//}

//TestCase( UniquePossibleValue )
//{
	//PossibleValues pv;
	//std::vector<unsigned> valuesToBeErased = {1,2,3,4,6,7,8,9};
	//unsigned uniqueValue = 5;
	//for( unsigned value : valuesToBeErased )
		//pv.erase(value);
	//check( pv.uniqueValue() == uniqueValue );
//}

//TestCase( PossibleValues_constants )
//{
	//checkEqual( PossibleValues::firstValue , 1 );
	//checkEqual( PossibleValues::lastValue , 9 );
	//checkEqual( PossibleValues::numberOfValues , 9 );
//}
