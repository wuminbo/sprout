#include "application.h"
#include "SDL.h"
#include "SdlDraw.h"
application::application(void)
{
}
//ģ����Ƶ��  
struct  
{  
    Uint32  pixformat;//���ظ�ʽ  
    int     w, h;//���  
    Uint8   *data;//��������  
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
    //r��g��b��a�ֱ�ռ8λ��Ҳ����һ���ֽ�  
    static Uint8 r = 0, g = 0, b = 0, a = 0;  
    //ģ��RGBA�仯  
    r += 10, g += 15, b += 20, a += 5;  
    //��ģ���ֵ��ֵ����������  
    Uint32 *pdst = (Uint32 *)frame.data;  
    Uint32 color = (r << 24) | (g << 16) | (b << 8) | a;  
    //ÿ������һ����ɫֵ  
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
        //ʹ��ģ�������������ֵ  
        fill_color_rgba8888();  
        //ʹ������ֵ��������  
		SdlDraw::getInstance()->draw(frame.data);
		SDL_Delay(1000);
    }  
  
    return 0;  
} 
application::~application(void)
{
}

void application::run(){
	 //��ʼ��SDL  
    if (SDL_Init(SDL_INIT_VIDEO) < 0)  
    {  
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL Timer SubSystem: %s\n", SDL_GetError());  
        quit(1);  
    }  
  
    screen_width = screen_height = 500;  
    frame.w = frame.h = 300;  
    frame.pixformat = SDL_PIXELFORMAT_RGBA8888;//���ظ�ʽ  
    frame.data = (Uint8 *)calloc(frame.w*frame.h*4, 1); //һ��������ɫֵ��Ҫ4���ֽڣ�32λ��r8��g8��b8��a8��  
    //��������  
    SDL_Window *p_screen;  
    p_screen = SDL_CreateWindow("video test",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  
        screen_width, screen_height, SDL_WINDOW_RESIZABLE);  
    if (NULL == p_screen)  
    {  
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s\n", SDL_GetError());  
        quit(2);  
    }  
    //������Ⱦ��  
    p_render = SDL_CreateRenderer(p_screen, -1, 0);  
    if (NULL == p_render)  
    {  
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create renderer: %s\n", SDL_GetError());  
        quit(3);  
    }  
    //��������  
    p_texture = SDL_CreateTexture(p_render, frame.pixformat, SDL_TEXTUREACCESS_STREAMING, frame.w, frame.h);  
    if (NULL == p_texture)  
    {  
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture: %s\n", SDL_GetError());  
        quit(4);  
    }  
  
    //�����߳�ģ����Ƶ���ݸ���  
    SDL_Thread *video_thread = SDL_CreateThread(video_process, NULL, NULL);  
  
    //��Ϣѭ��  
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
  
    //����  
    SDL_DestroyTexture(p_texture);  
    SDL_DestroyRenderer(p_render);  
    SDL_DestroyWindow(p_screen);  
    free(frame.data);  
    SDL_Quit();  
}
