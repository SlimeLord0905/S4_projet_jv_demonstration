#include <stdio.h>

#define SIZE_X 80
#define SIZE_Y 45


#define IDLE 1
#define JUMP 2
#define MIDAIR 3
#define LANDING 4

const int initialBackground[SIZE_Y][SIZE_X] = {
    {4, 4, 4, 6, 6, 6, 6, 4, 4, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 5, 4, 4},
    {4, 4, 5, 4, 4, 5, 4, 4, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 5, 5},
    {4, 4, 4, 4, 4, 7, 6, 7, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4},
    {4, 4, 4, 6, 7, 7, 6, 7, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4},
    {4, 4, 5, 6, 7, 7, 6, 7, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 5, 4, 5, 4, 4, 5, 5, 4},
    {4, 4, 5, 6, 7, 6, 6, 7, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 7, 6, 7, 5, 4, 4, 4, 5},
    {4, 4, 4, 6, 7, 6, 6, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 7, 6, 7, 7, 6, 4, 4, 4},
    {5, 5, 4, 6, 7, 6, 6, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 7, 6, 6, 7, 6, 5, 4, 4},
    {5, 5, 5, 6, 6, 6, 6, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 7, 6, 6, 7, 6, 5, 5, 4},
    {4, 5, 4, 6, 6, 6, 6, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 7, 6, 6, 6, 6, 4, 4, 5},
    {4, 5, 5, 6, 6, 6, 6, 6, 6, 4, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4},
    {4, 4, 4, 6, 6, 6, 6, 6, 5, 5, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4},
    {4, 4, 4, 6, 6, 5, 5, 4, 4, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4},
    {5, 5, 4, 4, 5, 5, 7, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 5, 4, 4},
    {4, 4, 5, 4, 4, 6, 7, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 5, 6, 6, 6, 6, 6, 6, 5, 5, 4},
    {4, 4, 4, 5, 6, 6, 7, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 5, 5, 6, 6, 6, 6, 6, 4, 4, 5},
    {4, 4, 4, 7, 6, 6, 7, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 7, 4, 4, 5, 5, 6, 6, 4, 4, 4},
    {4, 5, 5, 7, 6, 6, 6, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 7, 6, 6, 7, 4, 4, 5, 4, 4, 4},
    {4, 4, 4, 7, 6, 6, 6, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 7, 6, 6, 7, 6, 5, 4, 4, 4, 4},
    {4, 4, 4, 7, 6, 6, 6, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 7, 6, 6, 7, 6, 6, 5, 4, 4, 5},
    {5, 5, 4, 4, 6, 6, 6, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 7, 6, 6, 7, 6, 6, 6, 4, 4, 5},
    {4, 5, 5, 5, 5, 5, 5, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 6, 7, 6, 6, 6, 4, 4, 5},
    {5, 5, 4, 7, 7, 7, 5, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 6, 7, 6, 6, 6, 4, 4, 4},
    {4, 5, 5, 7, 7, 6, 7, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 6, 7, 6, 6, 6, 4, 4, 4},
    {4, 4, 4, 6, 7, 6, 7, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4},
    {4, 4, 4, 6, 7, 6, 7, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4},
    {5, 4, 4, 6, 6, 6, 6, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 6, 6, 4, 5, 5, 5, 4, 4},
    {4, 5, 4, 6, 6, 6, 6, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 5, 5, 5, 4, 4, 4, 5, 4, 4},
    {4, 5, 5, 6, 6, 6, 6, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 7, 6, 6, 7, 6, 6, 4, 5, 4},
    {4, 4, 4, 4, 4, 6, 6, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 7, 6, 6, 7, 6, 6, 4, 4, 5},
    {4, 4, 4, 4, 4, 5, 5, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 7, 6, 6, 7, 6, 6, 4, 4, 4},
    {4, 4, 5, 6, 6, 6, 7, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 7, 6, 6, 6, 6, 6, 4, 4, 4},
    {4, 4, 5, 6, 6, 6, 7, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 7, 6, 6, 6, 6, 6, 4, 4, 4},
    {4, 5, 4, 6, 6, 6, 7, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 7, 6, 6, 6, 6, 6, 5, 5, 4},
    {5, 5, 4, 6, 6, 6, 7, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 7, 6, 6, 6, 6, 6, 4, 4, 5},
    {4, 4, 4, 6, 6, 6, 7, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 7, 6, 6, 6, 6, 6, 4, 4, 4},
    {4, 4, 4, 6, 6, 6, 6, 6, 8, 8, 8, 8, 14, 12, 13, 8, 8, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 8, 8, 8, 8, 8, 8, 8, 14, 12, 13, 8, 8, 8, 8, 11, 10, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4, 4},
    {5, 4, 4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 14, 12, 13, 8, 8, 8, 8, 8, 8, 8, 8, 11, 10, 8, 8, 8, 8, 8, 8, 8, 8, 8, 6, 6, 8, 6, 8, 11, 10, 8, 8, 8, 8, 14, 12, 13, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 14, 12, 13, 8, 8, 8, 8, 11, 10, 8, 8, 8, 8, 8, 9, 9, 8, 8, 8, 4, 4, 4},
    {5, 5, 4, 4, 8, 8, 8, 8, 8, 8, 8, 8, 14, 12, 13, 8, 8, 8, 8, 8, 8, 8, 8, 11, 10, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 11, 10, 8, 8, 8, 8, 14, 12, 13, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 14, 12, 13, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 4, 4, 4},
    {4, 4, 5, 5, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 14, 12, 13, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 14, 12, 13, 9, 9, 9, 9, 9, 9, 9, 9, 9, 12, 12, 12, 12, 9, 9, 9, 5, 5, 4},
    {4, 4, 4, 5, 5, 5, 5, 5, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 9, 12, 12, 12, 12, 12, 9, 9, 9, 9, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 4, 4, 5, 5},
    {4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4, 5, 5, 5, 5, 5},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
};
const int proceduralBackground[SIZE_Y-9][SIZE_X] = {
    {4, 4, 4, 6, 6, 6, 6, 4, 4, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 5, 4, 4},
    {4, 4, 5, 4, 4, 5, 4, 4, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 5, 5},
    {4, 4, 4, 4, 4, 7, 6, 7, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4},
    {4, 4, 4, 6, 7, 7, 6, 7, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4},
    {4, 4, 5, 6, 7, 7, 6, 7, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 5, 4, 5, 4, 4, 5, 5, 4},
    {4, 4, 5, 6, 7, 6, 6, 7, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 7, 6, 7, 5, 4, 4, 4, 5},
    {4, 4, 4, 6, 7, 6, 6, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 7, 6, 7, 7, 6, 4, 4, 4},
    {5, 5, 4, 6, 7, 6, 6, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 7, 6, 6, 7, 6, 5, 4, 4},
    {5, 5, 5, 6, 6, 6, 6, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 7, 6, 6, 7, 6, 5, 5, 4},
    {4, 5, 4, 6, 6, 6, 6, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 7, 6, 6, 6, 6, 4, 4, 5},
    {4, 5, 5, 6, 6, 6, 6, 6, 6, 4, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4},
    {4, 4, 4, 6, 6, 6, 6, 6, 5, 5, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4},
    {4, 4, 4, 6, 6, 5, 5, 4, 4, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4},
    {5, 5, 4, 4, 5, 5, 7, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 5, 4, 4},
    {4, 4, 5, 4, 4, 6, 7, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 5, 6, 6, 6, 6, 6, 6, 5, 5, 4},
    {4, 4, 4, 5, 6, 6, 7, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 5, 5, 6, 6, 6, 6, 6, 4, 4, 5},
    {4, 4, 4, 7, 6, 6, 7, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 7, 4, 4, 5, 5, 6, 6, 4, 4, 4},
    {4, 5, 5, 7, 6, 6, 6, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 7, 6, 6, 7, 4, 4, 5, 4, 4, 4},
    {4, 4, 4, 7, 6, 6, 6, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 7, 6, 6, 7, 6, 5, 4, 4, 4, 4},
    {4, 4, 4, 7, 6, 6, 6, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 7, 6, 6, 7, 6, 6, 5, 4, 4, 5},
    {5, 5, 4, 4, 6, 6, 6, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 7, 6, 6, 7, 6, 6, 6, 4, 4, 5},
    {4, 5, 5, 5, 5, 5, 5, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 6, 7, 6, 6, 6, 4, 4, 5},
    {5, 5, 4, 7, 7, 7, 5, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 6, 7, 6, 6, 6, 4, 4, 4},
    {4, 5, 5, 7, 7, 6, 7, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 6, 7, 6, 6, 6, 4, 4, 4},
    {4, 4, 4, 6, 7, 6, 7, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4},
    {4, 4, 4, 6, 7, 6, 7, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4},
    {5, 4, 4, 6, 6, 6, 6, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 6, 6, 4, 5, 5, 5, 4, 4},
    {4, 5, 4, 6, 6, 6, 6, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 5, 5, 5, 4, 4, 4, 5, 4, 4},
    {4, 5, 5, 6, 6, 6, 6, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 7, 6, 6, 7, 6, 6, 4, 5, 4},
    {4, 4, 4, 4, 4, 6, 6, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 7, 6, 6, 7, 6, 6, 4, 4, 5},
    {4, 4, 4, 4, 4, 5, 5, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 7, 6, 6, 7, 6, 6, 4, 4, 4},
    {4, 4, 5, 6, 6, 6, 7, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 7, 6, 6, 6, 6, 6, 4, 4, 4},
    {4, 4, 5, 6, 6, 6, 7, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 7, 6, 6, 6, 6, 6, 4, 4, 4},
    {4, 5, 4, 6, 6, 6, 7, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 7, 6, 6, 6, 6, 6, 5, 5, 4},
    {5, 5, 4, 6, 6, 6, 7, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 7, 6, 6, 6, 6, 6, 4, 4, 5},
    {4, 4, 4, 6, 6, 6, 7, 6, 6, 8, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 6, 8, 6, 6, 11, 10, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 6, 8, 6, 6, 6, 6, 14, 12, 13, 6, 6, 6, 6, 11, 10, 6, 6, 6, 6, 7, 6, 6, 6, 6, 6, 4, 4, 4},
};
   
int state = IDLE;
int clk = 1;

// player var 
int posX = 240;
int posY = 24;

int acc_X = 0;
int acc_y = 0; 

// screen offset
int offsetX = 240;
int offsetY = 40;

// actor1
//int posX = 0;
//int posY = 0;


void physics(){
    /*gestion de tout ce qui est deplacement dynamique et des colision avec les plateforme
    optionnel gt/n/ration du niveau ici si rapide si devient pllus complexe faire une fonction juste pour cela*/
}
void display(){
    /*commande d<affichage sur le PPU c<est la qu<on va utiliser l API*/

    printf("Etat : %d | Position : (%d, %d)\n", state, posX, posY);
}

//---------------------------------- Code test a supprimer plus tard -------------------------------------------------------------
int readButtonA() {
    static int frame = 0;
    frame++;
    // Pressé à partir de frame 10, relâché à frame 30 en gros comment on saute longtemps
    return (frame >= 10 && frame < 60) ? 1 : 0;
}


int simulatedTime = 0;

int getTime() {
    return simulatedTime;
}

int readJoystickX() {
    return 32;  // direction du joystick en x -128 a 128
}

int readJoystickY() {
    return 128;  // direction du joystick en x -128 a 128
}

//---------------------------------- Code test a supprimer plus tard -------------------------------------------------------------

void idle(){
    /*attendre la pression de la touche jump du joueur effectuer les phisyque des enemies et le display
    utiliser la frame d animation 1*/

    // Check si saut est appuyer
    int button = readButtonA(); // a voir en fonction de comment on get la manette

    // changement d'état pour JUMP
    if (button) {
        state = JUMP;
    }

    // affichage idle (jcp comment on va le coder)
    display();
}

void jump() {
    /*lecture du temps de pression de la touche jump et application du ratio X et Y selon le joystick
    effectuer les phisyque des enemies et le display
    utiliser la frame d animation 2*/

    static int charging = 0;
    static int jumpStartTime = -1;

    int button = readButtonA();
    int joyX = readJoystickX();
    int joyY = readJoystickY();

    int currentTime = getTime(); // a voir selon comment on fait le temps

    if (!charging && button) {
        // Démarrer la charge du saut (Comment on va aller haut)
        charging = 1;
        jumpStartTime = currentTime;
        printf(">> Debut de la charge\n");
    }

    if (charging) {
        int elapsed = currentTime - jumpStartTime;

        // Si on dépasse 2 secondes ou si on relâche a voir selon le gameplay
        if (!button || elapsed >= 2000) {
            if (elapsed > 1000) elapsed = 1000; // cap la charge max à 1s

            // puissance entre 0 et 10 a changer si besoin
            int power = (elapsed * 10) / 1000;

            acc_X = (joyX * power) / 128;
            acc_y = (-joyY * power) / 128;

            printf(">> Saut ! Puissance = %d | acc_X = %d | acc_y = %d\n", power, acc_X, acc_y);

            state = MIDAIR;

            charging = 0;
            jumpStartTime = -1;
        }
    }

    display();
}


void midair(){
    /*effectuer les phisyque des enemies et du joeur et le display
    detection des colision
    utiliser la frame d animation 3*/

    static int velocityY = 0;
    static int velX = 0; // on garde la vitesse horizontale

    const int gravity = 1;
    const int groundY = 24;

    // Appliquer acc initiale
    velocityY += acc_y;
    velX += acc_X;

    acc_y = 0;
    acc_X = 0;

    // Gravité
    velocityY += gravity;

    // Mouvement
    posY += velocityY;
    posX += velX;

    // --- Gestion des rebonds sur les murs ---
    if (posX < 0) {
        posX = 0;
        velX = -velX;
        printf(">> Rebond gauche\n");
    } else if (posX >= SIZE_X) {
        posX = SIZE_X - 1;
        velX = -velX;
        printf(">> Rebond droite\n");
    }

    // Si sol touché
    if (posY >= groundY) {
        posY = groundY;
        velocityY = 0;
        velX = 0;  // on arrête aussi horizontalement à l'atterrissage
        state = LANDING;
        printf(">> Atterrissage détecté\n");
    }

    // Affichage
    printf(">> MID-AIR: X=%d | Y=%d | velX=%d | velY=%d\n", posX, posY, velX, velocityY);
    display();
}


void landing(){
    /*effectuer les phisyque des enemies et du joeur et le display
    detection des colision
    transition vers le state idle au bout de quelque miliseconde a ajuster au feeling compter le delais en nombre de cycle 
    utiliser la frame d animation 2*/

    static int landingTimer = 0;
    const int landingDuration = 30; // en nombre de cycles (ajuste selon la vitesse)

    printf(">> LANDING... (timer: %d)\n", landingTimer);

    landingTimer++;

    if (landingTimer >= landingDuration) {
        state = IDLE;
        landingTimer = 0;
    }

    display();
}

int main() {
    while(1){
        // Petit delay pour ralentir l’exécution juste en test
        for (volatile int i = 0; i < 10000000; ++i);

        if(clk){
            if(state == IDLE){
                idle();
            }else if(state == JUMP){
                jump();
            }else if(state == MIDAIR){
                midair();
            }else if(state == LANDING){
                landing();
            }
        }

        // Incrémenter le temps simulé
        simulatedTime += 16;  // ~16ms = 60 fps
    }
    return 0;
}
