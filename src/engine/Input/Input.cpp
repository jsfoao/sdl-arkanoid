#include "Input.h"
#include <iostream>

Input::Input() {}
Input::~Input() {}

extern Input* n_input;

bool Input::GetKeyDown(int scancode)
{
	return n_input->keyStates[scancode] == KeyState::Down;
}

bool Input::GetKey(int scancode)
{
	return n_input->keys[scancode] == 1;
}

bool Input::GetKeyUp(int scancode)
{
	return n_input->keyStates[scancode] == KeyState::Up;
}

void Input::evaluateKeyState(int scancode)
{
	// No input
	if (n_input->keys[scancode] == false && n_input->keyDown[scancode] == false)
	{
		n_input->keyStates[scancode] = KeyState::None;
		return;
	}

	if (n_input->keys[scancode] == true && n_input->keyDown[scancode] == false)
	{
		n_input->keyDown[scancode] = true;
		n_input->keyStates[scancode] = KeyState::Down;
	}
	else if (n_input->keys[scancode] == false && n_input->keyDown[scancode] == true)
	{
		n_input->keyDown[scancode] = false;
		n_input->keyStates[scancode] = KeyState::Up;
	}
	else
	{
		n_input->keyStates[scancode] = KeyState::Hold;
	}
}