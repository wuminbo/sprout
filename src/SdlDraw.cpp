#include "SdlDraw.h"


static SdlDraw* m_instance = nullptr;

SdlDraw::SdlDraw(void)
{
}


SdlDraw::~SdlDraw(void)
{
	SDL_DestroyTexture(_textrue);  
    SDL_DestroyRenderer(_renderer);  
    SDL_DestroyWindow(_window);  
}



void SdlDraw::init(const char *title = "sprout", const int screen_width = 500, const int screen_height = 500)
{
	_frameWidth = 300;
	_frameHeight = 300;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "init fail :%s", SDL_GetError());
		SDL_Quit();  
	}
	_window = SDL_CreateWindow("video test",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  
        screen_width, screen_height, SDL_WINDOW_RESIZABLE);  
	if(NULL == _window)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "init fail :%s", SDL_GetError());
		SDL_Quit();  
	}

	_renderer = SDL_CreateRenderer(_window, -1, 0);
	if(NULL == _renderer)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "init fail :%s", SDL_GetError());
		SDL_Quit();  
	}
	_textrue = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, _frameWidth, _frameHeight);
}

void SdlDraw::draw(Uint8 *data)
{
	SDL_UpdateTexture(_textrue, NULL, data, _frameWidth*4);
	SDL_RenderClear(_renderer);
	SDL_RenderCopy(_renderer, _textrue, NULL, NULL);
	SDL_RenderPresent(_renderer);
}

SdlDraw* SdlDraw::getInstance()
{
	if(!m_instance)
	{
		m_instance = new SdlDraw();
		m_instance->init();
	}
	return m_instance;
}