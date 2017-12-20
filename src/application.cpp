#include "application.h"
#include "SDL.h"
#include "SdlDraw.h"
application::application(void)
{
}
//模拟视频流  
struct  
{  
    Uint32  pixformat;//像素格式  
    int     w, h;//宽高  
    Uint8   *data;//像素数据  
}frame;  
  
int screen_width  = 0;  
int screen_height = 0;  
int status = 0; // 1: request to stop; 2: stop  
SDL_Texture *p_texture = NULL;  
SDL_Renderer *p_render = NULL; 
static void quit(int rc)  
{  
    SDL_Quit();  
    exit(rc);  
}  
void fill_color_rgba8888()  
{  
    //r，g，b，a分别占8位，也就是一个字节  
    static Uint8 r = 0, g = 0, b = 0, a = 0;  
    //模拟RGBA变化  
    r += 10, g += 15, b += 20, a += 5;  
    //将模拟的值赋值给像素数据  
    Uint32 *pdst = (Uint32 *)frame.data;  
    Uint32 color = (r << 24) | (g << 16) | (b << 8) | a;  
    //每个像素一个颜色值  
    for (int i = 0; i < frame.w*frame.h; i++)  
    {  
        *pdst++ = color;  
    }  
} 
int SDLCALL video_process(void * data)  
{  
    int ret;   
    while (1)  
    {  
        if (1 == status)    // request to stop  
        {  
            status = 2;  
            break;  
        }  
        //使用模拟数据填充像素值  
        fill_color_rgba8888();  
        //使用像素值更新纹理  
		SdlDraw::getInstance()->draw(frame.data);
		SDL_Delay(1000);
    }  
  
    return 0;  
} 
application::~application(void)
{
}

void application::run(){
	 //初始化SDL  
    if (SDL_Init(SDL_INIT_VIDEO) < 0)  
    {  
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL Timer SubSystem: %s\n", SDL_GetError());  
        quit(1);  
    }  
  
    screen_width = screen_height = 500;  
    frame.w = frame.h = 300;  
    frame.pixformat = SDL_PIXELFORMAT_RGBA8888;//像素格式  
    frame.data = (Uint8 *)calloc(frame.w*frame.h*4, 1); //一个像素颜色值需要4个字节（32位：r8，g8，b8，a8）  
    //创建窗口  
    SDL_Window *p_screen;  
    p_screen = SDL_CreateWindow("video test",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  
        screen_width, screen_height, SDL_WINDOW_RESIZABLE);  
    if (NULL == p_screen)  
    {  
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s\n", SDL_GetError());  
        quit(2);  
    }  
    //创建渲染器  
    p_render = SDL_CreateRenderer(p_screen, -1, 0);  
    if (NULL == p_render)  
    {  
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create renderer: %s\n", SDL_GetError());  
        quit(3);  
    }  
    //创建纹理  
    p_texture = SDL_CreateTexture(p_render, frame.pixformat, SDL_TEXTUREACCESS_STREAMING, frame.w, frame.h);  
    if (NULL == p_texture)  
    {  
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture: %s\n", SDL_GetError());  
        quit(4);  
    }  
  
    //启动线程模拟视频数据更新  
    SDL_Thread *video_thread = SDL_CreateThread(video_process, NULL, NULL);  
  
    //消息循环  
    SDL_Event event;  
    while (status != 2)  
    {  
        SDL_WaitEvent(&event);  
        switch (event.type)  
        {  
        case SDL_QUIT:  
            status = 1;  
            break;  
        }  
    }  
  
    //清理  
    SDL_DestroyTexture(p_texture);  
    SDL_DestroyRenderer(p_render);  
    SDL_DestroyWindow(p_screen);  
    free(frame.data);  
    SDL_Quit();  
}
