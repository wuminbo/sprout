#include "application.h"
#include "SDL.h"
#include "SdlDraw.h"
#include "sprout_math.h"


Uint8 *frameData;
int frame_width = 300;
int frame_height = 300;

POLYF_4D poly1;
RENDER_4D_LIST render_list;
CAM_4D cam;
POINT_4D cam_pos;
VECTOR_4D cam_dir;

POINT_4D world_pos;

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

    initCamera(&cam, &cam_pos, &cam_dir, NULL, 50.0, 500.0, 90.0, frame_width, frame_height);
}

void loop()
{
	static float ang_y = 0;
	static MAT_4X4 rot_mat; 

	clearRenderList(&render_list);

	insertPoly4dToRenderList1(&render_list, poly1);

	buildXYZRotationMat4X4(0, ang_y, 0, &rot_mat);

	transformRenderList(&render_list, &rot_mat);

	TransModelToWorldCoor(&render_list, &world_pos);

	buildCame4DMatrixEuler(&cam);

	worldToCameraRenderList(&render_list, &cam);

	cameraToPerspectiveRenderList(&render_list, &cam);

	perspectiveToScreenRenderList(&render_list, &cam);

	fillFrameBuff(&render_list, frameData);

	SdlDraw::getInstance()->draw(frameData);

	if (++ang_y >= 360.0)
		ang_y = 0;
}


void GameMain()
{

	init();

    while(1)  
    {  
		loop();
       
    };
  
    free(frameData);
    SDL_Quit();  
}
