#pragma once
#include <iostream>
#include <stdio.h>
#include <SDL/SDL.h>

#pragma region Engine
class Engine
{
public:
	Engine();
	~Engine();

	void init(const char* title, int x, int y, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }

private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
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

struct Vector2
{
	int x;
	int y;

	Vector2 operator=(int& other);
	friend Vector2 operator+(Vector2 a, Vector2 b);
	friend Vector2 operator-(Vector2 a, Vector2 b);
	friend Vector2 operator*(Vector2 a, int b);
};







const float PI = 3.1415;

class Draw
{

};