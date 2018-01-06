#include <AppFunctions.h>

void createEmptySudokuGame(const char * fileName)
{
	SudokuGame sg;
	const char * extension = ".sudokugame";
	char fileNameWithExtension[200];
	strcpy(fileNameWithExtension , fileName);
	strcat(fileNameWithExtension , extension);
	sg.createFile(fileNameWithExtension,AppDefinition::problemDatasetName);
	return;
}

bool checkIsValidSudokuGame(const char * fileName, const char * datasetName)
{
	SudokuGame sg;
	sg.readFromFile(fileName, datasetName);
	return sg.isValid();
}

bool checkIsSolvedSudokuGame(const char * fileName, const char * datasetName)
{
	SudokuGame sg;
	sg.readFromFile(fileName, datasetName);
	return sg.isSolved();
}

bool solveSudokuGame(const char * fileName, const char * datasetName)
{
	SudokuGame sg;
	sg.readFromFile(fileName,datasetName);
	sg.solveForOnePossibleValue();
	sg.appendInFile(fileName,AppDefinition::solutionDatasetName);
	return sg.isSolved();
}

AppBehaviour selectBehaviour(const char * behaviourString)
{
	AppBehaviour selectedBehaviour = AppBehaviour::error;
	if( strcmp(behaviourString,"create_empty")==0 )
		selectedBehaviour = AppBehaviour::create_empty;
	else if( strcmp(behaviourString,"check")==0 )
			selectedBehaviour = AppBehaviour::check;
	else if( strcmp(behaviourString,"solved")==0 )
			selectedBehaviour = AppBehaviour::solved;
	else if( strcmp(behaviourString,"solve")==0 )
			selectedBehaviour = AppBehaviour::solve;
	return selectedBehaviour;
}

bool checkNumberOfInputs(const int argc)
{
	return argc==3;
}

void errorInvalidNumberOfArguments(void)
{
	std::cerr << std::endl << "Invalid number of arguments. Use:" << std::endl;
	std::cerr << std::endl << "\t$ program behaviour file_name" << std::endl;
	std::cerr << std::endl << "\tbehaviour = create_empty, check, solved, solve." << std::endl << std::endl;
	exit(EXIT_FAILURE);
}

void errorInvalidBehaviour(void)
{
	std::cerr << std::endl << "Invalid behaviour. Use:" << std::endl;
	std::cerr << std::endl << "\t$ program behaviour file_name" << std::endl;
	std::cerr << std::endl << "\tbehaviour = create_empty, check, solved, solve." << std::endl << std::endl;
	exit(EXIT_FAILURE);
}
