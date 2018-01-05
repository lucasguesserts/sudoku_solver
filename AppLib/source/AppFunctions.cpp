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
