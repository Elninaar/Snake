#include "physics.h"
#include "graph.h"
#include "GenericTypeDefs.h"
#include "BMA150.h"
#include "levels.h"
#include "math.h"
#include "oled.h"


signed short int g_devAccelerationX;
signed short int g_devAccelerationY;
signed short int g_devAccelerationZ;

signed short int g_devAccOffsetX = 0;
signed short int g_devAccOffsetY = 0;
signed short int g_devAccOffsetZ = 0;

float g_ballX, g_ballY, g_ballZ;
float foodX = 36;
float foodY = 36;

char score = 0;
char record = 0;

float g_ballVelX, g_ballVelY, g_ballVelZ;

float g_ballVeloX, g_ballVeloY, g_ballVeloZ;
signed short int VelXSigne, VelYSigne;
signed short int LastVelXSigne = 1;
signed short int LastVelYSigne = 1;
signed short int LastDirection = 0; // 0 signifie x et 1 signifie y

signed short int compteurFrame = 10;

signed short int Coord [50][2] = {{-10,-10},{-10,-10},{-10,-10},{-10,-10},{-10,-10},{-10,-10},{-10,-10},{-10,-10},
								  {-10,-10},{-10,-10},{-10,-10},{-10,-10},{-10,-10},{-10,-10},{-10,-10},{-10,-10},
								  {-10,-10},{-10,-10},{-10,-10},{-10,-10},{-10,-10},{-10,-10},{-10,-10},{-10,-10},
								  {-10,-10},{-10,-10},{-10,-10},{-10,-10},{-10,-10},{-10,-10},{-10,-10},{-10,-10},
								  {-10,-10},{-10,-10},{-10,-10},{-10,-10},{-10,-10},{-10,-10},{-10,-10},{-10,-10},
								  {-10,-10},{-10,-10},{-10,-10},{-10,-10},{-10,-10},{-10,-10},{-10,-10},{-10,-10},{-10,-10},{-10,-10}};
unsigned short int DimTabCoord = 2; //correspond au dimmension du tableau si dessus

unsigned char sens;

void ReadAccState()
{
	unsigned char lsb, msb;
	lsb = BMA150_ReadByte(BMA150_ACC_X_LSB);
	msb = BMA150_ReadByte(BMA150_ACC_X_MSB);
	
	g_devAccelerationX = (signed short int)(((unsigned short int)msb << 8) | (lsb));
	g_devAccelerationX /= 32;

	lsb = BMA150_ReadByte(BMA150_ACC_Y_LSB);
	msb = BMA150_ReadByte(BMA150_ACC_Y_MSB);
	
	g_devAccelerationY = (signed short int)(((unsigned short int)msb << 8) | (lsb));
	g_devAccelerationY /= 32;

	lsb = BMA150_ReadByte(BMA150_ACC_Z_LSB);
	msb = BMA150_ReadByte(BMA150_ACC_Z_MSB);
}

void Step()
{
	float dtime = 0.04f;
	float d;
	unsigned char i, j;
	static float time = 0.0f;

	time = time+dtime;

	ReadAccState();

	compteurFrame = compteurFrame-1;
	if(compteurFrame==0){

//*****************ON FAIT REVENIR LE SERPENT SI IL SORT*************************************
		//si on est en x
		if(g_ballVelX != 0){
			if (g_ballY >= 68){
					g_ballY = 4;
				}
			if (g_ballY <= -4){
				g_ballY = 60;
			}
			//si on est en x+
			if(g_ballVelX > 0){
				if (g_ballX > 132){
					g_ballX = 4;
				}	
			}
			//si on est en x-
			if(g_ballVelX < 0){
				if (g_ballX < -4){
					g_ballX = 124;
				}
			}				
		}
		//si on est en y
		else{
			if (g_ballX >= 132){
				g_ballX = 4;
			}
			if (g_ballX <= -4){
				g_ballX = 124;
			}
			// si on se dirigent en y+
			if(g_ballVelY > 0){
				if (g_ballY > 68){
					g_ballY = 4;
				}
			}
			//si on se dirigent en y-
			if(g_ballVelY < 0){
				if (g_ballY < -4){
					g_ballY = 60;
				}		
			}				
		}

// ************************* ON DECALE LES COORDONEES DANS LE TABLEAU *******************
	    for (i = DimTabCoord-1; i > 0; --i){
	    	for (j = 0; j < 2; j++){
	    		Coord [i][j] = Coord [i-1][j];
	    	}
	    }

// ******* STOCKER LES COORDONNEES DANS LA PREMIERE LIGNE DU TABLEAU 2 DIMENSIONS *******
	    Coord[0][0] =g_ballX; 
	    Coord[0][1] =g_ballY; 

// ****************** RENDRE LA TRAJECTOIRE RECTILIGNE EMPECHER LES DEMI-TOUR ***********

	    g_ballVelX = (float)(g_devAccelerationY-g_devAccOffsetY)/2.0f;
	    g_ballVelY = (float)(g_devAccelerationX-g_devAccOffsetX)/2.0f;
		
		//G_BALLVELOX ET G_BALLVELOX SONT MIS EN VALEUR ABSOLUE POUR COMPARER LES VITESSES
	    g_ballVeloX = g_ballVelX;
	    g_ballVeloY = g_ballVelY;

	    //ON STOCKE LE SIGNE DE LA VITESSE ACTUELLE 
	    VelXSigne = 1;
	    VelYSigne = 1;
		if(g_ballVeloX<0){
			g_ballVeloX = -g_ballVeloX;
			VelXSigne = -1;
		}
		if(g_ballVeloY<0){
			g_ballVeloY = -g_ballVeloY;
			VelYSigne = -1;
		}

		//si on est en x
		if(g_ballVeloX > g_ballVeloY){
			switch(VelXSigne+VelXSigne){
				//axe x - 
				case -2:
					sens = 1;
					break;
				//axe x + 
				case 2:
					sens = 2;
					break;
			}
			//si on était déjà en x la fois passée
			if(LastDirection == 0){
				//si on veut passé de veut passé de + vers -
				if(LastVelXSigne*VelXSigne == -1){
					g_ballVelY = 0;
					g_ballVelX = 20*LastVelXSigne;
					if(g_ballVelX < 0){
						sens = 1; 
					}
					else{
						sens = 2;
					}
				}
				else{
					g_ballVelY = 0;
					g_ballVelX = 20*VelXSigne;
				}
			}
			else{
				g_ballVelY = 0;
				g_ballVelX = 20*VelXSigne;
			}
		}
		//si on est en y
		else{
			switch(VelYSigne+VelYSigne){
				case -2:
					//axe y - 					
					sens = 3;				
					break;
				case 2:
					//axe y +
					sens = 4;					
					break;
			}
			//si on était déjà en y la fois passée
			if(LastDirection == 1){
				//si on veut passé de veut passé de + vers -
				if(LastVelYSigne*VelYSigne == -1){
					g_ballVelX = 0;
					g_ballVelY = 20*LastVelYSigne;
					if(g_ballVelY < 0){
						sens = 3; 
					}
					else{
						sens = 4;
					}						
				}
				else{
					g_ballVelX = 0;
					g_ballVelY = 20*VelYSigne;
				}
			}
			else{
				g_ballVelX = 0;
				g_ballVelY = 20*VelYSigne;	
			}
		}

		// CALCULS DES NOUVELLES COORDONNEES 
		g_ballX = g_ballX + (float)g_ballVelX * dtime * 10;
		g_ballY = g_ballY + (float)g_ballVelY * dtime * 10;
        
		//ON GARDE EN MEMOIRE LES SIGNES DES VITESSES DANS LASTVELXSIGNE ET LASTVELYSIGNE
		if(g_ballVeloX >g_ballVeloY){
			LastDirection = 0;	
		}
		else{
			LastDirection = 1;
		}
		if(g_ballVelX<0){
			LastVelXSigne = -1;
		}
		else{
			LastVelXSigne = 1;
		}
		if(g_ballVelY<0){
			LastVelYSigne = -1;
		}
		else{
			LastVelYSigne = 1;
		}

// ************************* CHECKER COLISION DU SNAKE **************************************
		for (i = 1; i < DimTabCoord-1; ++i)
		{
			if((Coord[0][0] == Coord[i][0]) && (Coord[0][1] == Coord[i][1])){
				g_endGame = 1;
				if(score > record){
					record = score;
				}
			}
		}

// ********************** CHECKER LES COLLISIONS ENTRE FOOD ET SNAKE ***********************
		if((Coord[0][0] == foodX) && (Coord[0][1] == foodY)){ 
			foodX = 4 + (rand() % 16)*8;
			foodY = 4 + (rand() % 8)*8;
			if(DimTabCoord < 50){
				DimTabCoord++;
			}
			score++;
		}

// ********************** ADAPTATION DE LA VITESSE DU SNAKE ********************************			
		compteurFrame = 10;
		if(score > 30){
			compteurFrame = 6;
		}
		else{
			if(score > 14){
				compteurFrame = 7;
			}
			else{
				if(score > 9){
					compteurFrame = 8;
				}
				else{
					if(score > 3){
						compteurFrame = 9;
					}
				}				
			}
		}					
	}
	return;
}




