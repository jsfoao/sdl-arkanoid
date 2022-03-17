#include "LevelManager.h"
#include "../src/engine/Engine.h"
#include <vector>

#define WIDTH 12
#define HEIGHT 12

std::vector<Entity*> mapEntities;

void GenerateMap(std::string levelStr)
{
	for (size_t i = 0; i < WIDTH * HEIGHT; i++)
	{
		float x = i % WIDTH;
		float y = i / WIDTH;

		if (levelStr[i] == '#')
		{
			Entity* newEntity = Instantiate(new Brick(), Vector2((x + 0.5f) * 50, (y + 0.5f) * 25));
			mapEntities.push_back(newEntity);
		}
		else if (levelStr[i] == '$')
		{
			Entity* newEntity = Instantiate(new Wall(), Vector2((x + 0.5f) * 50, (y + 0.5f) * 25));
			mapEntities.push_back(newEntity);
		}
	}
}

std::string LoadFile(std::string path)
{
	std::ifstream inFile;
	inFile.open(path);
	if (!inFile)
	{
		std::cerr << "Unable to open file on " + path;
		exit(1);
	}

	std::cout << "Loaded level on " + path << std::endl;

	std::string levelStr;
	std::string line;
	while (!inFile.eof()) 
	{
		inFile >> line;
		levelStr += line;
	}
	return levelStr;
}