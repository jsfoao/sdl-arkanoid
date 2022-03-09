#pragma once
struct Color
{
	int r, g, b, a;
	Color();
	~Color();

	Color(int r, int g, int b, int a);

	const static Color Red;
	const static Color Green;
	const static Color Blue;
	const static Color White;
	const static Color Black;
};