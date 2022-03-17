#include "LevelManager.h"
#include "../src/engine/Engine.h"

#define WIDTH 16
#define HEIGHT 12

std::ifstream inFile;

void GenerateMap(std::string levelStr)
{
	for (size_t i = 0; i < WIDTH * HEIGHT; i++)
	{
		float x = i % WIDTH;
		float y = i / WIDTH;

		if (levelStr[i] == '#')
		{
			Instantiate(new Brick(), Vector2((x + 0.5) * 50, (y + 0.5) * 25));
		}
		else if (levelStr[i] == '$')
		{
			Instantiate(new Wall(), Vector2((x + 0.5) * 50, (y + 0.5) * 25));
		}
	}
}

std::string LoadFile(std::string path)
{
	inFile.open(path);
	if (!inFile)
	{
		std::cerr << "Unable to open file on " + path;
		exit(1);
	}

	std::cout << "Found file on " + path << std::endl;

	std::string levelStr;
	std::string line;
	while (!inFile.eof()) 
	{
		inFile >> line;
		levelStr += line;
	}
	return levelStr;
}