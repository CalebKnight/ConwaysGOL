#include <stdlib.h>
#include <stdio.h>
#include "game.h"

int main(int argc, char *argv[])
{
    char *cellFile;
    int cycles;
    if (argc == 3)
    {
        cellFile = argv[1];
        cycles = atoi(argv[2]);
        if (cycles <= 0)
        {
            printf("Invalid number of cycles\n");
        }
        else
        {
            gameOfLifeLoop(cellFile, cycles);
        }
    }
    else
    {
        printf("Usage: ./GameOfLife <cellFile> <cycles>\n");
    }
    return 1;
}
