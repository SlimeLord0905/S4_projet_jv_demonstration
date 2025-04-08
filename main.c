#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE_X 80
#define SIZE_Y 45

//limites horizontales du joueur, ajustés à la dernière tuile valable
#define ARBRE_DROIT 608
#define ARBRE_GAUCHE 24


#define IDLE 1
#define JUMP 2
#define MIDAIR 3
#define LANDING 4
#define DEATH 5

//plateformes
#define MAX_PLATFORMS 10
#define PLATFORM_HEIGHT 2
#define PLATFORM_MIN_WIDTH 4
#define PLATFORM_MAX_WIDTH 9
#define PLATFORM_SPACING_Y 48

#define TILE_SIZE 8

typedef enum {
    NO_COLLISION,
    COLLISION_LEFT,
    COLLISION_RIGHT,
    COLLISION_BOTTOM,
    COLLISION_LANDING
} CollisionType;

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
int posX = 312;
int posY = 320;

int acc_X = 0;
int acc_y = 0; 

// screen offset
//revérifier les valeurs??
int offsetX = 240;
int offsetY = 40;

//structure de données pour les plateformes
typedef struct{
    int x;
    int y;
    int width;
    int active;
} Platform;


Platform platforms[MAX_PLATFORMS];
int platformCount = 0; //nombre de plateformes affichees


CollisionType physics(){
    /*gestion de tout ce qui est deplacement dynamique et des colision avec les plateforme
    optionnel gt/n/ration du niveau ici si rapide si devient pllus complexe faire une fonction juste pour cela*/
    //player 
    int left = posX;
    int right = posX + 16;
    int top = posY;
    int bottom = posY + 16;

    for (int i = 0; i < platformCount; i++) {
        if (!platforms[i].active) continue;

        int pLeft = platforms[i].x;
        int pRight = platforms[i].x + platforms[i].width;
        int pTop = platforms[i].y;
        int pBottom = platforms[i].y + 8;  // On suppose une hauteur de plateforme de 8

        // Vérifie la superposition (collision générale)
        if (right > pLeft && left < pRight && bottom > pTop && top < pBottom) {

            int dxLeft = right - pLeft;
            int dxRight = pRight - left;
            int dyTop = bottom - pTop;
            int dyBottom = pBottom - top;

            // On cherche la plus petite pénétration
            if (dyTop < dxLeft && dyTop < dxRight && dyTop < dyBottom)
                return COLLISION_LANDING;
            else if (dyBottom < dxLeft && dyBottom < dxRight)
                return COLLISION_BOTTOM;
            else if (dxLeft < dxRight)
                return COLLISION_LEFT;
            else
                return COLLISION_RIGHT;
        }
    }

    return NO_COLLISION;
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

//s'assurer que les plateformes sont des alignées à des valeurs de tuiles
int alignToTile(int value) {
    return (value / TILE_SIZE) * TILE_SIZE;
}

int generatePlatform(int index, int y, int previousX){
    
    platforms[index].width = (rand() % (PLATFORM_MAX_WIDTH - PLATFORM_MIN_WIDTH + 1)) + PLATFORM_MIN_WIDTH;
    int platformWidthinPixels = platforms[index].width * TILE_SIZE;

    int maxX = previousX + 200;    //distances horizontales maximales des plateformes pour que le joeur puisse sauter
    int minX = previousX - 200;

    //bornes arbres
    if(minX < ARBRE_GAUCHE) minX = ARBRE_GAUCHE;
    if(maxX > ARBRE_DROIT - platformWidthinPixels)
        maxX = ARBRE_DROIT - platformWidthinPixels;

    int range = (maxX - minX) / TILE_SIZE + 1;
    //int choice = rand() % range;
    int offsetPlateform = (rand() % range) * TILE_SIZE;
    int newX = minX + offsetPlateform;
    int newY = alignToTile(y);

    if(newY < 0){
        platforms[index].width = (rand() % (PLATFORM_MAX_WIDTH - PLATFORM_MIN_WIDTH + 1)) + PLATFORM_MIN_WIDTH;
        platformWidthinPixels = platforms[index].width * TILE_SIZE;
        int tempX = rand() % (ARBRE_DROIT - platformWidthinPixels - ARBRE_GAUCHE) + ARBRE_GAUCHE;
        int tempY = rand() % (360 - 0);
        newX = alignToTile(tempX);
        newY = alignToTile(tempY);
    }

    for (int i = 0; i < index; i++) {
        if (!platforms[i].active) continue;
        int left1 = newX;
        int right1 = newX + platformWidthinPixels;
        int top1 = newY;
        int bottom1 = newY + PLATFORM_HEIGHT * TILE_SIZE;
    
        int left2 = platforms[i].x;
        int right2 = platforms[i].x + platforms[i].width * TILE_SIZE;
        int top2 = platforms[i].y;
        int bottom2 = platforms[i].y + PLATFORM_HEIGHT * TILE_SIZE;
    
        if (!(right1 <= left2 || left1 >= right2 || bottom1 <= top2 || top1 >= bottom2)) {
            // chevauchement détecté
            printf("entered");
            platforms[index].active = 0;
            return 0;
        }
    }    
    platforms[index].x = newX;
    platforms[index].y=newY;
    platforms[index].active = 1;
    //générer une position aléatoire pour la plateforme alignée avec les tuiles

    printf(">> Génération de la plateforme %d\n", index);
    printf(">> Range : [%d, %d]\n", minX, maxX);
    printf(">> Position : (%d, %d)\n", platforms[index].x, platforms[index].y);
    printf(">> Largeur : %d\n", platforms[index].width);
    printf(">> Actif : %d\n", platforms[index].active);
    printf(">> Position précédente : %d\n", previousX);
    return 1;
}

void initPlatforms(){
    int startY = posY - 48;
    int currentX = posX;

    for(int i = 0; i < MAX_PLATFORMS; i++){
        int success = 0;
        int attemptY = startY;

        while (!success && attemptY < posY + 200) {
            success = generatePlatform(i, attemptY, currentX);
            attemptY += TILE_SIZE * 3; // on descend un peu si ça échoue
        }

        currentX = platforms[i].x;
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
    CollisionType colPlateforme = physics();

    if(colPlateforme == COLLISION_LEFT){
        velX = -velX;
        printf(">> Rebond gauche\n");
    }else if(colPlateforme ==COLLISION_RIGHT){
        velX = -velX;
        printf(">> Rebond droite\n");
    }else if(colPlateforme ==COLLISION_BOTTOM){
        velocityY = -velocityY;
        printf(">> Rebond haut\n");
    }else if(colPlateforme ==COLLISION_LANDING){
        velocityY = 0;
        velX = 0;  // on arrête aussi horizontalement à l'atterrissage
        state = LANDING;
        printf(">> Atterrissage détecté\n");
    }
    

    // a ajuster une fois qu<on a un visuel 
    if(posY < (offsetY + 120)){
        offsetY = posY -120;
    }else if(posY > (offsetY + 240)){
        state = DEATH;
        printf("death");
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
    int clock = 0;
    while(state != DEATH && clock < 1000){
        // Petit delay pour ralentir l’exécution juste en test
        for (volatile int i = 0; i < 10000000; ++i);
        clock++;
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