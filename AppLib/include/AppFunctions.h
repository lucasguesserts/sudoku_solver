#ifndef APP_FUNCTIONS_H
#define APP_FUNCTIONS_H

#include <SudokuGame.h>
#include <AppDefinition.h>

void createEmptySudokuGame(const char * fileName);
bool checkIsValidSudokuGame(const char * fileName, const char * datasetName);
bool checkIsSolvedSudokuGame(const char * fileName, const char * datasetName);
bool solveSudokuGame(const char * fileName, const char * datasetName);

#endif
