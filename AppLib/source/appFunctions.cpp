#include <appFunctions.h>

const char * problemDatasetName = "Problem";

void createEmptySudokuGame(const char * fileName)
{
	SudokuGame sg;
	const char * extension = ".sudokugame";
	char fileNameWithExtension[200];
	strcpy(fileNameWithExtension , fileName);
	strcat(fileNameWithExtension , extension);
	sg.createFile(fileNameWithExtension,problemDatasetName);
	std::cout << std::endl << "Successfully created empty sudoku game '" << fileNameWithExtension << "'." << std::endl;
	std::cout << std::endl << "Use hdfview to edit the file." << std::endl;
	std::cout << std::endl;
	return;
}

void checkSudokuGame(const char * fileName, const char * datasetName)
{
	SudokuGame sg;
	sg.readFromFile(fileName, datasetName);
	if (sg.isValid())
		std::cout << "File" << " '" << fileName << "/" << datasetName << "' " << "is VALID." << std::endl << std::endl;
	else
		std::cout << "File" << " '" << fileName << "/" << datasetName << "' " << "is INVALID." << std::endl << std::endl;
	return;
}
