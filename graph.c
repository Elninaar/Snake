#include "graph.h"
#include "oled.h"
#include "physics.h"
#include "levels.h"


#pragma idata graph_buffer
unsigned char g_graphBuffer[128][8];
#pragma idata

unsigned char * g_graphBufPtr = &g_graphBuffer[0][0];

void FlushGraphics();
void loadLevel(unsigned char l);


void FlushGraphics()
{
	int i, j;

	for (j = 0; j < 8; j++)
	{
		WriteCommand(0xB0+j);
		WriteCommand(0x00+OFFSET);
		WriteCommand(0x10);

		for (i = 0; i < 128; i++)
		{
			WriteData(g_graphBufPtr[i+128*j]);
		}
	}
}

void Fill(unsigned char clr)
{
	int i;
	for (i = 0; i < 1024; i++)
	{
		g_graphBufPtr[i] = clr;
	}
}


void DrawFood(unsigned char x,unsigned char y){
	int i, j;
	for (i = -2; i < 3; i++){
		for (j = -2; j < 3; j++){
			if(x+i > 127){
			}
			else{
				if(x+i < 0){
				}
				else{
					SetPx(x+i,y+j);
				}
			}
		}
	}
}


void DrawPix(unsigned char x,unsigned char y){
	if(x > 127){
	}
	else{
		if(x < 0){
		}
		else{
			SetPx(x,y);
		}

	}
}

void DrawSnake(unsigned char x, unsigned char y, signed short int Coordinates [50][2],unsigned char d)
{
	int i, j;
	switch(d){
		case 2:
			DrawPix(x-4,y-4); DrawPix(x-4,y-3); DrawPix(x-4,y-2); DrawPix(x-4,y-1); DrawPix(x-4,y+0); DrawPix(x-4,y+1); DrawPix(x-4,y+2); DrawPix(x-4,y+3); DrawPix(x-4,y+4);
			DrawPix(x-3,y-4); DrawPix(x-3,y-3); DrawPix(x-3,y-2); DrawPix(x-3,y-1); DrawPix(x-3,y+0); DrawPix(x-3,y+1); DrawPix(x-3,y+2); DrawPix(x-3,y+3); DrawPix(x-3,y+4);
			DrawPix(x-2,y-4); /*SetPx(x-2,y-3); SetPx(x-2,y-2); SetPx(x-2,y-1);*/ DrawPix(x-2,y+0); /*SetPx(x-2,y+1); SetPx(x-2,y+2); SetPx(x-2,y+3);*/ DrawPix(x-2,y+4);
			DrawPix(x-1,y-4); DrawPix(x-1,y-3); /*SetPx(x-1,y-2);*/ DrawPix(x-1,y-1); DrawPix(x-1,y+0); DrawPix(x-1,y+1); /*SetPx(x-1,y+2);*/ DrawPix(x-1,y+3); DrawPix(x-1,y+4);
			DrawPix(x+0,y-4); /*SetPx(x+0,y-3); SetPx(x+0,y-2); SetPx(x+0,y-1);*/ DrawPix(x+0,y+0); /*SetPx(x+0,y+1); SetPx(x+0,y+2); SetPx(x+0,y+3);*/ DrawPix(x+0,y+4);
			DrawPix(x+1,y-4); DrawPix(x+1,y-3); DrawPix(x+1,y-2); DrawPix(x+1,y-1); DrawPix(x+1,y+0); DrawPix(x+1,y+1); DrawPix(x+1,y+2); DrawPix(x+1,y+3); DrawPix(x+1,y+4);
			DrawPix(x+2,y-4); DrawPix(x+2,y-3); DrawPix(x+2,y-2); DrawPix(x+2,y-1); DrawPix(x+2,y+0); DrawPix(x+2,y+1); DrawPix(x+2,y+2); DrawPix(x+2,y+3); DrawPix(x+2,y+4);					
			DrawPix(x+3,y-4); DrawPix(x+3,y-3); DrawPix(x+3,y-2); /*SetPx(x+3,y-1);*/ DrawPix(x+3,y+0); /*SetPx(x+3,y+1)*/; DrawPix(x+3,y+2); DrawPix(x+3,y+3); DrawPix(x+3,y+4);	
			DrawPix(x+4,y-4); DrawPix(x+4,y-3); DrawPix(x+4,y-2); DrawPix(x+4,y-1); DrawPix(x+4,y+0); DrawPix(x+4,y+1); DrawPix(x+4,y+2); DrawPix(x+4,y+3); DrawPix(x+4,y+4);	
			break;
		case 3:
			DrawPix(x-4,y-4); DrawPix(x-4,y-3); DrawPix(x-4,y-2); DrawPix(x-4,y-1); DrawPix(x-4,y+0); DrawPix(x-4,y+1); DrawPix(x-4,y+2); DrawPix(x-4,y+3); DrawPix(x-4,y+4);
			DrawPix(x-3,y-4); DrawPix(x-3,y-3); DrawPix(x-3,y-2); DrawPix(x-3,y-1); /*SetPx(x-3,y+0);*/ DrawPix(x-3,y+1); /*SetPx(x-3,y+2);*/ DrawPix(x-3,y+3); DrawPix(x-3,y+4);
			DrawPix(x-2,y-4); DrawPix(x-2,y-3); DrawPix(x-2,y-2); DrawPix(x-2,y-1); /*SetPx(x-2,y+0);*/ /*SetPx(x-2,y+1);*/ /*SetPx(x-2,y+2);*/ DrawPix(x-2,y+3); DrawPix(x-2,y+4);
			DrawPix(x-1,y-4); /*SetPx(x-1,y-3);*/ DrawPix(x-1,y-2); DrawPix(x-1,y-1); /*SetPx(x-1,y+0);*/ DrawPix(x-1,y+1); /*SetPx(x-1,y+2);*/ DrawPix(x-1,y+3); DrawPix(x-1,y+4);
			DrawPix(x+0,y-4); DrawPix(x+0,y-3); DrawPix(x+0,y-2); DrawPix(x+0,y-1); DrawPix(x+0,y+0); DrawPix(x+0,y+1); DrawPix(x+0,y+2); DrawPix(x+0,y+3); DrawPix(x+0,y+4);
			DrawPix(x+1,y-4); /*SetPx(x+1,y-3);*/ DrawPix(x+1,y-2); DrawPix(x+1,y-1); /*SetPx(x+1,y+0);*/ DrawPix(x+1,y+1); /*SetPx(x+1,y+2);*/ DrawPix(x+1,y+3); DrawPix(x+1,y+4);
			DrawPix(x+2,y-4); DrawPix(x+2,y-3); DrawPix(x+2,y-2); DrawPix(x+2,y-1); /*SetPx(x+2,y+0);*/ /*SetPx(x+2,y+1);*/ /*SetPx(x+2,y+2);*/ DrawPix(x+2,y+3); DrawPix(x+2,y+4);					
			DrawPix(x+3,y-4); DrawPix(x+3,y-3); DrawPix(x+3,y-2); DrawPix(x+3,y-1); /*SetPx(x+3,y+0);*/ DrawPix(x+3,y+1); /*SetPx(x+3,y+2);*/ DrawPix(x+3,y+3); DrawPix(x+3,y+4);	
			DrawPix(x+4,y-4); DrawPix(x+4,y-3); DrawPix(x+4,y-2); DrawPix(x+4,y-1); DrawPix(x+4,y+0); DrawPix(x+4,y+1); DrawPix(x+4,y+2); DrawPix(x+4,y+3); DrawPix(x+4,y+4);
			break;
		case 1:
			DrawPix(x-4,y-4); DrawPix(x-4,y-3); DrawPix(x-4,y-2); DrawPix(x-4,y-1); DrawPix(x-4,y+0); DrawPix(x-4,y+1); DrawPix(x-4,y+2); DrawPix(x-4,y+3); DrawPix(x-4,y+4);
			DrawPix(x-3,y-4); DrawPix(x-3,y-3); DrawPix(x-3,y-2); /*SetPx(x-3,y-1);*/ DrawPix(x-3,y+0); /*SetPx(x-3,y+1);*/ DrawPix(x-3,y+2); DrawPix(x-3,y+3); DrawPix(x-3,y+4);
			DrawPix(x-2,y-4); DrawPix(x-2,y-3); DrawPix(x-2,y-2); DrawPix(x-2,y-1); DrawPix(x-2,y+0); DrawPix(x-2,y+1); DrawPix(x-2,y+2); DrawPix(x-2,y+3); DrawPix(x-2,y+4);
			DrawPix(x-1,y-4); DrawPix(x-1,y-3); DrawPix(x-1,y-2); DrawPix(x-1,y-1); DrawPix(x-1,y+0); DrawPix(x-1,y+1); DrawPix(x-1,y+2); DrawPix(x-1,y+3); DrawPix(x-1,y+4);
			DrawPix(x+0,y-4);/* SetPx(x+0,y-3); SetPx(x+0,y-2); SetPx(x+0,y-1);*/ DrawPix(x+0,y+0); /*SetPx(x+0,y+1); SetPx(x+0,y+2); SetPx(x+0,y+3);*/ DrawPix(x+0,y+4);
			DrawPix(x+1,y-4); DrawPix(x+1,y-3); /*SetPx(x+1,y-2);*/ DrawPix(x+1,y-1); DrawPix(x+1,y+0); DrawPix(x+1,y+1); /*SetPx(x+1,y+2);*/ DrawPix(x+1,y+3); DrawPix(x+1,y+4);
			DrawPix(x+2,y-4); /*SetPx(x+2,y-3); SetPx(x+2,y-2); SetPx(x+2,y-1);*/ DrawPix(x+2,y+0); /*SetPx(x+2,y+1); SetPx(x+2,y+2); SetPx(x+2,y+3);*/ DrawPix(x+2,y+4);					
			DrawPix(x+3,y-4); DrawPix(x+3,y-3); DrawPix(x+3,y-2); DrawPix(x+3,y-1); DrawPix(x+3,y+0); DrawPix(x+3,y+1); DrawPix(x+3,y+2); DrawPix(x+3,y+3); DrawPix(x+3,y+4);	
			DrawPix(x+4,y-4); DrawPix(x+4,y-3); DrawPix(x+4,y-2); DrawPix(x+4,y-1); DrawPix(x+4,y+0); DrawPix(x+4,y+1); DrawPix(x+4,y+2); DrawPix(x+4,y+3); DrawPix(x+4,y+4);
			break;
		case 4:
			DrawPix(x-4,y-4); DrawPix(x-4,y-3); DrawPix(x-4,y-2); DrawPix(x-4,y-1); DrawPix(x-4,y+0); DrawPix(x-4,y+1); DrawPix(x-4,y+2); DrawPix(x-4,y+3); DrawPix(x-4,y+4);
			DrawPix(x-3,y-4); DrawPix(x-3,y-3); /*SetPx(x-3,y-2);*/ DrawPix(x-3,y-1); /*SetPx(x-3,y+0);*/ DrawPix(x-3,y+1); DrawPix(x-3,y+2); DrawPix(x-3,y+3); DrawPix(x-3,y+4);
			DrawPix(x-2,y-4); DrawPix(x-2,y-3);/* SetPx(x-2,y-2);*//* SetPx(x-2,y-1);*/ /*SetPx(x-2,y+0);*/ DrawPix(x-2,y+1); DrawPix(x-2,y+2); DrawPix(x-2,y+3); DrawPix(x-2,y+4);
			DrawPix(x-1,y-4); DrawPix(x-1,y-3); /*SetPx(x-1,y-2);*/ DrawPix(x-1,y-1); /*SetPx(x-1,y+0);*/ DrawPix(x-1,y+1); DrawPix(x-1,y+2); /*SetPx(x-1,y+3); */DrawPix(x-1,y+4);
			DrawPix(x+0,y-4); DrawPix(x+0,y-3); DrawPix(x+0,y-2); DrawPix(x+0,y-1); DrawPix(x+0,y+0); DrawPix(x+0,y+1); DrawPix(x+0,y+2); DrawPix(x+0,y+3); DrawPix(x+0,y+4);
			DrawPix(x+1,y-4); DrawPix(x+1,y-3); /*SetPx(x+1,y-2);*/ DrawPix(x+1,y-1); /*SetPx(x+1,y+0);*/ DrawPix(x+1,y+1); DrawPix(x+1,y+2); /*SetPx(x+1,y+3);*/ DrawPix(x+1,y+4);
			DrawPix(x+2,y-4); DrawPix(x+2,y-3); /*SetPx(x+2,y-2);*/ /*SetPx(x+2,y-1);*/ /*SetPx(x+2,y+0);*/ DrawPix(x+2,y+1); DrawPix(x+2,y+2); DrawPix(x+2,y+3); DrawPix(x+2,y+4);					
			DrawPix(x+3,y-4); DrawPix(x+3,y-3); /*SetPx(x+3,y-2); */DrawPix(x+3,y-1); /*SetPx(x+3,y+0);*/ DrawPix(x+3,y+1); DrawPix(x+3,y+2); DrawPix(x+3,y+3); DrawPix(x+3,y+4);	
			DrawPix(x+4,y-4); DrawPix(x+4,y-3); DrawPix(x+4,y-2); DrawPix(x+4,y-1); DrawPix(x+4,y+0); DrawPix(x+4,y+1); DrawPix(x+4,y+2); DrawPix(x+4,y+3); DrawPix(x+4,y+4);
			break;
		case 5:
			for (i = -4; i < 5; i++){
				for (j = -4; j < 5; j++){
					DrawPix(x+i,y+j);
				}
			}
			break;
	}
}


void DrawScene()
{
	unsigned char i;
	// Clear the scene
	Fill(0x00);
	// Send all data to screen driver
	for (i = 0; i < DimTabCoord; ++i)
	{
		if(i == 0){
			DrawSnake((unsigned char)Coord[i][0], (unsigned char)Coord[i][1], Coord, sens);
		}
		else
			DrawSnake((unsigned char)Coord[i][0], (unsigned char)Coord[i][1], Coord, 5);
	}
	DrawFood(foodX, foodY);
	FlushGraphics();
}
