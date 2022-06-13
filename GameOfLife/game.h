#ifndef GAME_H
#define GAME_H
void gameOfLifeLoop(char *fileName, int cycles);
void printBoard(int **startingBoard, int rows, int cols);
int **performCycle(int **startingBoard, int rows, int cols);
int getCellState(int **startingBoard, int rows, int cols, int i, int j);
int getNeighbourCount(int **startingBoard, int rows, int cols, int i, int j);
int **createBlankBoard(int rows, int cols);
#endif