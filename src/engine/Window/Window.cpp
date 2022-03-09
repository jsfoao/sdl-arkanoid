#include "Window.h"

Window::Window()
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	sdl_window = SDL_CreateWindow(title, x, y, width, height, flags);
}

Window::~Window(){}

Window::Window(const char* title, int x, int y, int width, int height, bool fullscreen)
{
	this->title = title;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->fullscreen = fullscreen;

	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	sdl_window = SDL_CreateWindow(title, x, y, width, height, flags);
}