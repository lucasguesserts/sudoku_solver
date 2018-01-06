#include <cstdlib>
#include <iostream>
#include <vector>
#include <cstring>

#include <PossibleValues.h>

#include <Cell.h>
#include <Group.h>
#include <Row.h>
#include <Column.h>
#include <Rectangle.h>
#include <SudokuGame.h>

#include <AppFunctions.h>
#include <AppDefinition.h>

int main(const int argc, const char * const argv[])
{
	const char * fileName = argv[2];
	const char * datasetName;
	if ( ! checkNumberOfInputs(argc) ) errorInvalidNumberOfArguments();
	AppBehaviour behaviour = selectBehaviour(argv[1]);
	switch(behaviour)
	{
		case AppBehaviour::create_empty:
			createEmptySudokuGame(argv[2]);
			break;
		case AppBehaviour::check:
			datasetName = AppDefinition::problemDatasetName;
			std::cout << "'" << fileName << "/" << datasetName << "' ";
			if( checkIsValidSudokuGame(fileName,datasetName) )
				std::cout << "is VALID." << std::endl << std::endl;
			else
				std::cout << "is INVALID." << std::endl << std::endl;
			break;
		case AppBehaviour::solved:
			datasetName = AppDefinition::solutionDatasetName;
			std::cout << "'" << fileName << "/" << datasetName << "' ";
			if( checkIsSolvedSudokuGame(fileName,datasetName) )
				std::cout << "is SOLVED." << std::endl << std::endl;
			else
				std::cout << "is UNSOLVED ." << std::endl << std::endl;
			break;
		case AppBehaviour::solve:
			bool wasSolved;
			datasetName = AppDefinition::problemDatasetName;
			wasSolved = solveSudokuGame(fileName,datasetName);
			std::cout << "'" << fileName << "/" << datasetName << "' ";
			if(wasSolved)
				std::cout << "SOLVED." << std::endl << std::endl;
			else
				std::cout << "CANNOT be SOLVED." << std::endl << std::endl;
			break;
		default:
			errorInvalidBehaviour();
	}
	exit(EXIT_SUCCESS);
}
