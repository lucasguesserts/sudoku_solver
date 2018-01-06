#ifndef APP_FUNCTIONS_H
#define APP_FUNCTIONS_H

#include <cstdlib>
#include <cstring>
#include <iostream>

#include <SudokuGame.h>
#include <AppDefinition.h>

void createEmptySudokuGame(const char * fileName);
bool checkIsValidSudokuGame(const char * fileName, const char * datasetName);
bool checkIsSolvedSudokuGame(const char * fileName, const char * datasetName);
bool solveSudokuGame(const char * fileName, const char * datasetName);
AppBehaviour selectBehaviour(const char * behaviourString);
bool checkNumberOfInputs(const int argc);

void errorInvalidNumberOfArguments(void);
void errorInvalidBehaviour(void);

#endif
