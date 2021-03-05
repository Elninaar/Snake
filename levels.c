
#define LEVELS_C

#include "physics.h"
#include "graph.h"
#include "levels.h"

struct graphWall g_walls[MAX_WALLS];
struct physWall g_physWalls[MAX_WALLS];
struct physWallMover g_physWallMovers[MAX_WALLS_MOVERS];
struct Hole g_holes[MAX_HOLES];
unsigned char g_usedWalls;
unsigned char g_usedWallMovers;
unsigned char g_usedHoles;
unsigned char g_level;
unsigned char g_endGame = 0;

unsigned char g_levelEndX, g_levelEndY;

void level1();
void level2();
void level3();
void level4();
void level5();

void resetBall(unsigned char x, unsigned char y)
{
	g_ballX = x;
	g_ballY = y;
}

void level0()
{
	resetBall(28,28);
}

void level1()
{}

void level2()
{}

void level3()
{}

void level4()
{}

void level5()
{}

void loadLevel(unsigned char l)
{
	switch(l)
	{
		case 0:
			level0();
			break;

		case 1:
			level1();
			break;

		case 2:
			level2();
			break;

		case 3:
			level3();
			break;

		case 4:
			level4();
			break;

		case 5:
			level5();
			break;

		case LEVELS:
			g_endGame = 1;
			break;
	}
}

