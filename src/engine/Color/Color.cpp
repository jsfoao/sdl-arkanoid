#include "Color.h"

Color::Color()
{
	r = 0;
	g = 0;
	b = 0;
	a = 0;
}
Color::~Color(){}

Color::Color(int r, int g, int b, int a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

const Color Color::Red = Color(255, 0, 0, 255);
const Color Color::Green = Color(0, 255, 0, 255);
const Color Color::Blue = Color(0, 0, 255, 255);
const Color Color::White = Color(255, 255, 255, 255);
const Color Color::Black = Color(0, 0, 0, 255);