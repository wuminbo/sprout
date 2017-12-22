#pragma once
#include "SDL.h"

class SdlDraw
{
public:
	SdlDraw(void);
	~SdlDraw(void);
	void init(const char *title, const int screen_width, const int screen_height);
	void draw(Uint8 *data);
	static SdlDraw *getInstance();
private:
	SDL_Window *_window;
	SDL_Texture *_textrue;
	SDL_Renderer *_renderer;

	int _frameWidth, _frameHeight;
};

