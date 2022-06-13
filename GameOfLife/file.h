#ifndef FILE_H
#define FILE_H
int **getRowsAndColumns(char *fileName);
void freeRowsAndColumns(int **rowsAndColumns);
int intFromSubstring(char *string, int start);
int **getStartingBoard(char *fileName, int rows, int cols);
void freeStartingBoard(int **startingBoard, int rows);
int getTempStringLength(int rows, int cols);
#endif