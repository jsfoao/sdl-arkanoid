#pragma once
#include <iostream>
#include <stdio.h>
#include <SDL/SDL.h>
#include "Vector2.h"
#include "GameObject.h"

#pragma region Input
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
#pragma endregion

#pragma region Time
class Time
{
public:
	Time();
	~Time();

public:
	float deltaTime;
};
#pragma endregion

#pragma region Engine
class Engine
{
public:
	Engine();
	~Engine();

	void init(const char* title, int x, int y, int width, int height, bool fullscreen);

	void handleEvents();
	void start();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }

private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	Input* input;
};
#pragma endregion