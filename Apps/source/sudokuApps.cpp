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

#include <appFunctions.h>

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
