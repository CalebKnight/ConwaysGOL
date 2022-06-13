#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "game.h"
#include "file.h"

void gameOfLifeLoop(char *fileName, int cycles)
{
    int rows = 0;
    int cols = 0;
    int **startingBoard;
    int i;
    int **rowsAndColumns = getRowsAndColumns(fileName);
    if (rowsAndColumns != NULL)
    {
        rows = rowsAndColumns[0][0];
        cols = rowsAndColumns[1][0];
    }
    startingBoard = getStartingBoard(fileName, rows, cols);

    if (rowsAndColumns == NULL || startingBoard == NULL)
    {
        /* In order to get around the fact that frees are different depending on if a file is not found or not we just free these Null pointers instead if there is an error*/
        printf("Error: Could not read file.\n");
        free(rowsAndColumns);
        free(startingBoard);
    }
    else
    {
        for (i = 0; i < cycles; i++)
        {
            system("clear");
            printBoard(startingBoard, rows, cols);
            startingBoard = performCycle(startingBoard, rows, cols);
            sleep(1);
        }
        freeStartingBoard(startingBoard, rows);
        freeRowsAndColumns(rowsAndColumns);
    }
}

int **performCycle(int **startingBoard, int rows, int cols)
{
    int i;
    int j;
    int **newBoard = createBlankBoard(rows, cols);

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            newBoard[i][j] = getCellState(startingBoard, rows, cols, i, j);
        }
    }
    freeStartingBoard(startingBoard, rows);
    return (newBoard);
}

int **createBlankBoard(int rows, int cols)
{
    int i;
    int j;
    int **board = (int **)malloc(sizeof(int *) * rows);
    for (i = 0; i < rows; i++)
    {
        board[i] = (int *)malloc(sizeof(int) * cols);
    }
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            board[i][j] = 0;
        }
    }
    return (board);
}

int getCellState(int **startingBoard, int rows, int cols, int i, int j)
{
    int status;
    if (startingBoard[i][j] == 2)
    {
        status = 0;
    }
    else if (startingBoard[i][j] == 1)
    {
        int neighbourCount = getNeighbourCount(startingBoard, rows, cols, i, j);
        if (neighbourCount < 2 || neighbourCount > 3)
        {
            status = 0;
        }
        else if (neighbourCount == 2 || neighbourCount == 3)
        {
            status = 1;
        }
        else
        {
            status = 2;
        }
    }
    else
    {
        int neighbourCount = getNeighbourCount(startingBoard, rows, cols, i, j);
        if (neighbourCount == 3)
        {
            status = 1;
        }
        else
        {
            status = 0;
        }
    }
    return (status);
}

int getNeighbourCount(int **startingBoard, int rows, int cols, int i, int j)
{
    int count = 0;
    /*Right*/
    if (j < cols - 1 && startingBoard[i][j + 1] == 1)
    {
        count++;
    }
    /*Left*/
    if (j > 0 && startingBoard[i][j - 1] == 1)
    {
        count++;
    }
    /*Up*/
    if (i < rows - 1 && startingBoard[i + 1][j] == 1)
    {
        count++;
    }
    /*Down*/
    if (i > 0 && startingBoard[i - 1][j] == 1)
    {
        count++;
    }
    /*UpLeft*/
    if (i > 0 && j > 0 && startingBoard[i - 1][j - 1] == 1)
    {
        count++;
    }
    /*UpRight*/
    if (i > 0 && j < cols - 1 && startingBoard[i - 1][j + 1] == 1)
    {
        count++;
    }
    /*DownLeft*/
    if (i < rows - 1 && j > 0 && startingBoard[i + 1][j - 1] == 1)
    {
        count++;
    }
    /*DownRight*/
    if (i < rows - 1 && j < cols - 1 && startingBoard[i + 1][j + 1] == 1)
    {
        count++;
    }

    return (count);
}

void printBoard(int **startingBoard, int rows, int cols)
{
    int i;
    int j;

    printf("\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {

            if (startingBoard[i][j] == 1)
            {
                printf("\033[0;107m");
            }
            else
            {
                printf("\033[0;100m");
            }
            if (j == 0)
            {
                printf("\t");
            }
            printf(" ");
            printf("\033[0m");
        }
        printf("\n");
    }
    printf("\n");
}
