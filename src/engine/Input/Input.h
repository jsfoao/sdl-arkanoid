#pragma once
#include "SDL/SDL.h"

enum class KeyState
{
	None,
	Down,
	Hold,
	Up
};
class Input
{
public:
	bool keys[SDL_NUM_SCANCODES] = { false };
protected:
	bool keyDown[SDL_NUM_SCANCODES] = { false };
	KeyState keyStates[SDL_NUM_SCANCODES] = { KeyState::None };

public:
	Input();
	~Input();

	static bool GetKey(int scancode);
	static bool GetKeyDown(int scancode);
	static bool GetKeyUp(int scancode);
	static void evaluateKeyState(int scancode);
};