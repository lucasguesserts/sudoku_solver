#include <AppFunctions.h>

void createEmptySudokuGame(const char * fileName)
{
	SudokuGame sg;
	const char * extension = ".sudokugame";
	char fileNameWithExtension[200];
	strcpy(fileNameWithExtension , fileName);
	strcat(fileNameWithExtension , extension);
	sg.createFile(fileNameWithExtension,AppDefinition::problemDatasetName);
	//std::cout << std::endl << "Successfully created empty sudoku game '" << fileNameWithExtension << "'." << std::endl;
	//std::cout << std::endl << "Use hdfview to edit the file." << std::endl;
	//std::cout << std::endl;
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
