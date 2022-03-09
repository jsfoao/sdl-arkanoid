#include <SDL/SDL.h>
#include "../Vector/Vector2.h"

class Window
{
public:
	const char* title;
	int x, y;
	int width, height;
	bool fullscreen;
	SDL_Window* sdl_window;

public:
	Window();
	~Window();

	Window(const char* title, int x, int y, int width, int height, bool fullscreen);
};