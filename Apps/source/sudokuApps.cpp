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

const char * problemDatasetName = "Problem";
void createEmptySudokuGame(const char * fileName);
void checkSudokuGame(const char * filename);

int main(const int argc, const char * const argv[])
{
	if(argc!=2)
	{
		std::cerr << std::endl << "Invalid number of arguments. Use:" << std::endl;
		std::cerr << std::endl << "\t$ program file_name" << std::endl << std::endl;
		exit(EXIT_FAILURE);
	}
	createEmptySudokuGame(argv[1]);
	exit(EXIT_SUCCESS);
}

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

void checkSudokuGame(const char * filename, const char * datasetName)
{
	SudokuGame sg;
	sg.readFromFile(fileName, datasetName);
	if (sg.isValid())
		std::cout << "File" << " '" << fileName << "/" << datasetName << "' " << "is VALID." << std::endl << std::endl;
	else
		std::cout << "File" << " '" << fileName << "/" << datasetName << "' " << "is INVALID." << std::endl << std::endl;
	return;
}
