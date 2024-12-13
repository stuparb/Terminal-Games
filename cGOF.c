#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WIDTH 20
#define HEIGHT 20

void printGrid(int grid[HEIGHT][WIDTH])
{
    system("clear");
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            printf("%c", grid[i][j] ? '#' : '.');
        }
        printf("\n");
    }
}

int countNeighbours(int grid[HEIGHT][WIDTH], int x, int y)
{
    int cnt = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
                continue;
            int neighbourX = x + i;
            int neighbourY = y + j;
            if (neighbourX >= 0 && neighbourX < HEIGHT && neighbourY >= 0 && neighbourY < WIDTH)
            {
                cnt += grid[neighbourX][neighbourY];
            }
        }
    }
    return cnt;
}

void updateGrid(int grid[HEIGHT][WIDTH])
{
    int newGrid[HEIGHT][WIDTH] = {0};
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            int neighbours = countNeighbours(grid, i, j);
            if (grid[i][j] == 1)
            {
                newGrid[i][j] = (neighbours == 2 || neighbours == 3) ? 1 : 0;
            }
            else
            {
                newGrid[i][j] = (neighbours == 3) ? 1 : 0;
            }
        }
    }

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            grid[i][j] = newGrid[i][j];
        }
    }
}

int main()
{
    int grid[HEIGHT][WIDTH] = {0};

    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            grid[i][j] = rand() % 2;
        }
    }

    while (1)
    {
        printGrid(grid);
        updateGrid(grid);
        usleep(200000); 
    }

    return 0;
}


/*
-----------------------------------------RULES-----------------------------------------
Any live cell with fewer than two live neighbours dies, as if by underpopulation.
Any live cell with two or three live neighbours lives on to the next generation.
Any live cell with more than three live neighbours dies, as if by overpopulation.
Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
*/