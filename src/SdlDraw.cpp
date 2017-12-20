#include "SdlDraw.h"


static SdlDraw* m_instance = nullptr;

SdlDraw::SdlDraw(void)
{
}


SdlDraw::~SdlDraw(void)
{
}

void SdlDraw::init(const char *title = "sprout", const int width = 500, const int height = 500)
{
	_frameWidth = 300;
	_frameHeight = 300;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "init fail :%s", SDL_GetError());
	}
	_window = SDL_CreateWindow("sprout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,width,height,SDL_WINDOW_RESIZABLE);
	if(NULL == _window)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "init fail :%s", SDL_GetError());
	}

	_renderer = SDL_CreateRenderer(_window, -1, 0);
	if(NULL == _renderer)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "init fail :%s", SDL_GetError());
	}
	_textrue = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
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