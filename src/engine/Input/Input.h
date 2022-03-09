#pragma once
#include "SDL/SDL.h"

class Input
{
public:
	bool keys[SDL_NUM_SCANCODES];
public:
	Input();
	~Input();

	bool GetKeyDown(int scancode);
	bool GetKeyUp(int scancode);
};