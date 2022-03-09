#include "Input.h"

Input::Input() {}
Input::~Input() {}

bool Input::GetKeyDown(int scancode)
{
	return keys[scancode] == true;
}

bool Input::GetKeyUp(int scancode)
{
	return keys[scancode] == false;
}