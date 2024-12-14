#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define CLEAR_SCREEN() printf("\033[H\033[J")

const char *numbers[10][5] = {
    {"  ##  ", " #  # ", " #  # ", " #  # ", "  ##  "}, // 0
    {"   #  ", "  ##  ", "   #  ", "   #  ", "  ### "}, // 1
    {"  ##  ", " #  # ", "   #  ", "  #   ", " #### "}, // 2
    {" #### ", "    # ", "  ### ", "    # ", " #### "}, // 3
    {"   ## ", "  # # ", " #  # ", " #####", "    # "}, // 4
    {" #### ", " #    ", " #### ", "    # ", " #### "}, // 5
    {"  ### ", " #    ", " #### ", " #  # ", "  ##  "}, // 6
    {" #####", "    # ", "   #  ", "  #   ", "  #   "}, // 7
    {"  ##  ", " #  # ", "  ##  ", " #  # ", "  ##  "}, // 8
    {"  ##  ", " #  # ", "  ### ", "    # ", "  ##  "}  // 9
};

void printNumber(int num, int x, int y)
{
    int randColor = 31 + rand() % 7;

    printf("\033[%dm", randColor);

    for (int i = 0; i < 5; i++)
    {
        printf("\033[%d;%dH%s", y + i, x, numbers[num][i]);
    }
}

void printColon(int x, int y)
{

    printf("\033[%d;%dH  #  ", y + 1, x - 1);
    printf("\033[%d;%dH  #  ", y + 3, x - 1);
}

void drawClock(int hour, int minute, int second)
{
    CLEAR_SCREEN();

    printNumber(hour / 10, 5, 5);
    printNumber(hour % 10, 12, 5);

    printColon(19, 5);

    printNumber(minute / 10, 22, 5);
    printNumber(minute % 10, 29, 5);

    printColon(36, 5);

    printNumber(second / 10, 39, 5);
    printNumber(second % 10, 46, 5);

    fflush(stdout);
}

int main()
{
    //printf("\033[?25l");

    time_t now;
    struct tm *currentTime;

    while (1)
    {
        now = time(NULL);
        currentTime = localtime(&now);

        int hour = currentTime->tm_hour;
        int minute = currentTime->tm_min;
        int second = currentTime->tm_sec;

        drawClock(hour, minute, second);

        sleep(1);
    }
    //printf("\033[?25h");

    return 0;
}
