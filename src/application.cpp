#include "application.h"
#include "SDL.h"
#include "SdlDraw.h"
#include "math.h"


Uint8 *frameData;
int frame_width = 300;
int frame_height = 300;

POLYF_4D poly1;



void init()
{
    frameData = (Uint8 *)calloc(frame_width*frame_height*4, 1); 
    poly1.vlist[0].x = 0;
    poly1.vlist[0].y = 50;
    poly1.vlist[0].z = 0;
    poly1.vlist[0].w = 1;

    poly1.vlist[1].x = 50;
    poly1.vlist[1].y = -50;
    poly1.vlist[1].z = 0;
    poly1.vlist[1].w = 1;

    poly1.vlist[2].x = -50;
    poly1.vlist[2].y = -50;
    poly1.vlist[2].z = 0;
    poly1.vlist[2].w = 1;
}

void loop()
{
	static float ang_y = 0;
	static MAT_4X4 rot_mat; 
	
}

void GameMain()
{

	init()

    while (1)  
    {  
		
		SdlDraw::getInstance()->draw(frameData);
       
    }  
  
    free(frameData);
    SDL_Quit();  
}
