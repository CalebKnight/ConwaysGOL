#include <stdlib.h>
#include <stdio.h>
#include "file.h"

/*Get rows of columns from the first line of snake.txt and return them as a int array*/
int **getRowsAndColumns(char *fileName)
{
    FILE *file = fopen(fileName, "r");
    int **rowsAndColumns;
    if (file != NULL)
    {
        char *string = (char *)malloc(sizeof(char) * 7);
        rowsAndColumns = (int **)malloc(sizeof(int *) * 2);
        rowsAndColumns[0] = (int *)malloc(sizeof(int));
        rowsAndColumns[1] = (int *)malloc(sizeof(int));
        string = fgets(string, 7, file);
        *rowsAndColumns[0] = intFromSubstring(string, 0);
        /* This is a solution to support both single digits and double digits without a rewrite of the code */
        if (string[4] == '\n')
        {
            *rowsAndColumns[1] = intFromSubstring(string, 2);
        }
        else
        {
            *rowsAndColumns[1] = intFromSubstring(string, 3);
        }
        free(string);
        fclose(file);
    }
    else
    {
        rowsAndColumns = NULL;
    }
    return (rowsAndColumns);
}

int **getStartingBoard(char *fileName, int rows, int cols)
{
    int i;
    int j;
    char c;
    int **startingBoard;
    FILE *file = fopen(fileName, "r");
    if (file != NULL)
    {
        char *tempString = (char *)malloc(sizeof(char) * (100));
        startingBoard = (int **)malloc(sizeof(int *) * rows + 1);
        for (i = 0; i < rows; i++)
        {
            startingBoard[i] = (int *)malloc(sizeof(int) * cols + 1);
        }
        i = 0;
        j = 0;
        c = fgetc(file);
        fgets(tempString, getTempStringLength(rows, cols), file);
        while (i < rows && c != EOF)
        {

            printf("loop | i %d | j %d | %c\n", i, j, c);
            if (c == '\n')
            {
                j = 0;
                i++;
            }
            else if (c == '0' || c == '1')
            {
                startingBoard[i][j] = c - '0';
                j++;
            }
            c = fgetc(file);
        }
        fclose(file);
        free(tempString);
    }
    else
    {
        startingBoard = NULL;
    }
    return (startingBoard);
}

int getTempStringLength(int rows, int cols)
{
    if (rows < 10 && cols < 10)
    {
        return 5;
    }
    else if (rows < 10 && cols >= 10)
    {
        return 6;
    }
    else if (rows >= 10 && cols < 10)
    {
        return 6;
    }
    else
    {
        return 8;
    }
}

void freeStartingBoard(int **startingBoard, int rows)
{
    int i;
    for (i = 0; i < rows; i++)
    {
        free(startingBoard[i]);
    }
    free(startingBoard);
}

/*Free rows and columns from memory*/
void freeRowsAndColumns(int **rowsAndColumns)
{
    free(rowsAndColumns[0]);
    free(rowsAndColumns[1]);
    free(rowsAndColumns);
}

/*Converts a substring of double digits into a single integer*/
/*Is not applicable to 3 digit strings as it is hard coded to double digits*/
int intFromSubstring(char *string, int start)
{
    int number;
    char *subString = (char *)malloc(sizeof(char) * 3);
    subString[0] = string[start];
    subString[1] = string[start + 1];
    /* Need to add a terminator to the string to prevent atoi from having a read error */
    subString[2] = '\0';
    number = atoi(subString);
    free(subString);
    return number;
}