#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE_X 80
#define SIZE_Y 45

//limites horizontales du joueur, ajustés à la dernière tuile valable
#define ARBRE_DROIT 24
#define ARBRE_GAUCHE 608


#define IDLE 1
#define JUMP 2
#define MIDAIR 3
#define LANDING 4

//plateformes
#define MAX_PLATFORMS 10
#define PLATFORM_HEIGHT 2
#define PLATFORM_MIN_WIDTH 4
#define PLATFORM_MAX_WIDTH 9
#define PLATFORM_SPACING_Y 50

#define TILE_SIZE 8


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
int posX = 360;
int posY = 360;

int acc_X = 0;
int acc_y = 0; 

// screen offset
//revérifier les valeurs??
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

//structure de données pour les plateformes
typedef struct{
    int x;
    int y;
    int width;
    int active;
} Platform;

Platform platforms[MAX_PLATFORMS];
int platformCount = 0; //nombre de plateformes affichees

//s'assurer que les plateformes sont des alignées à des valeurs de tuiles
int alignToTile(int value) {
    return (value / TILE_SIZE) * TILE_SIZE;
}

void generatePlatform(int index, int y, int previousX){
    platforms[index].width = (rand() % (PLATFORM_MAX_WIDTH - PLATFORM_MIN_WIDTH + 1)) + PLATFORM_MIN_WIDTH;

    int platformWidthinPixels = platforms[index].width * TILE_SIZE;

    int maxX = previousX + 200;    //distances horizontales maximales des plateformes pour que le joeur puisse sauter
    int minX = previousX - 200;

    //bornes arbres
    if(minX < ARBRE_GAUCHE) minX = ARBRE_GAUCHE;
    if(maxX > ARBRE_DROIT - platformWidthinPixels)
        maxX = ARBRE_DROIT - platformWidthinPixels;

    //aligner minX et maxX
    minX = alignToTile(minX);
    maxX = alignToTile(maxX);

    //générer une position aléatoire pour la plateforme alignée avec les tuiles
    int range = (maxX - minX) / TILE_SIZE + 1;
    int choice = rand() % range;

    platforms[index].x = minX + (choice * TILE_SIZE);
    platforms[index].y = alignToTile(y);
}

void initPlatforms(){
    int startY = posY + 40;
    int refX = posX;
    for(int i = 0; i < MAX_PLATFORMS; i++){
        generatePlatform(i, startY, refX);
        refX = platforms[i].x;
        startY -= PLATFORM_SPACING_Y;
    }
}

void reutilisationPlatforms(){
    for(int i = 0; i < MAX_PLATFORMS; i++){
        if(platforms[i].y > offsetY + SIZE_Y * TILE_SIZE) {
            //la remettre plus haut
            int highest = platforms[0].y;
            for(int j = 1; j < MAX_PLATFORMS; j++){
                if(platforms[j].y < highest) 
                highest = platforms[j].y;
                generatePlatform(i, highest - PLATFORM_SPACING_Y, platforms[i].x);
            }
        }
    }
}


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
    if (posX < ARBRE_GAUCHE) {
        posX = ARBRE_GAUCHE;
        velX = -velX;
        printf(">> Rebond gauche\n");
    } else if (posX > ARBRE_DROIT) {
        posX = ARBRE_DROIT;
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
    srand(time(NULL));

    int startY = alignToTile(posY - 48);
    int lastX = alignToTile(posX);

    for (int i = 0; i < MAX_PLATFORMS; i++) {
        generatePlatform(i, startY, lastX);
        printf("Plateforme %d => X: %d, Y: %d, Width: %d\n", i, platforms[i].x, platforms[i].y, platforms[i].width);
        lastX = platforms[i].x;
        startY = alignToTile(startY - PLATFORM_SPACING_Y);
    }
    // while(1){
    //     // Petit delay pour ralentir l’exécution juste en test
    //     for (volatile int i = 0; i < 10000000; ++i);

    //     if(clk){
    //         if(state == IDLE){
    //             idle();
    //         }else if(state == JUMP){
    //             jump();
    //         }else if(state == MIDAIR){
    //             midair();
    //         }else if(state == LANDING){
    //             landing();
    //         }
    //     }

    //     // Incrémenter le temps simulé
    //     simulatedTime += 16;  // ~16ms = 60 fps
    // }
    return 0;
}
