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

int main(const int argc, const char * const argv[])
{
	const char * fileName = argv[2];
	if(argc != 3)
	{
		std::cerr << std::endl << "Invalid number of arguments. Use:" << std::endl;
		std::cerr << std::endl << "\t$ program behaviour file_name" << std::endl;
		std::cerr << std::endl << "\tbehaviour = create_empty, check, solved, solve." << std::endl << std::endl;
		exit(EXIT_FAILURE);
	}
	switch(argv[1])
		case "create_empty":
			createEmptySudokuGame(argv[2]);
			break;
		case "check":
			const char * datasetName = AppDefinition::problemDatasetName;
			std::cout << "'" << filename << "/" << datasetName << "' ";
			if( checkIsValidSudokuGame(fileName,datasetName) )
				std::cout << "is VALID." << std::endl << std::endl;
			else
				std::cout << "is INVALID." << std::endl << std::endl;
			break;
		case "solved":
			const char * datasetName = AppDefinition::solutionDatasetName;
			std::cout << "'" << filename << "/" << datasetName << "' ";
			if( checkIsSolvedSudokuGame(fileName,datasetName) )
				std::cout << "is SOLVED." << std::endl << std::endl;
			else
				std::cout << "is UNSOLVED ." << std::endl << std::endl;
			break;
		case "solve":
			bool wasSolved;
			const char * datasetName = AppDefinition::problemDatasetName;
			wasSolved = solveSudokuGame(fileName,datasetName) 
			std::cout << "'" << filename << "/" << datasetName << "' ";
			if(wasSolved)
				std::cout << "SOLVED." << std::endl << std::endl;
			else
				std::cout << "CANNOT be SOLVED." << std::endl << std::endl;
			break;
		default:
			std::cerr << std::endl << "Invalid behaviour. Use:" << std::endl;
			std::cerr << std::endl << "\t$ program behaviour file_name" << std::endl;
			std::cerr << std::endl << "\tbehaviour = create_empty, check, solved, solve." << std::endl << std::endl;
			exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
