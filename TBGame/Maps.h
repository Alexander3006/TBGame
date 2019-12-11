#pragma once
#include <SFML/Graphics.hpp>
#include "PreprocessConst.h"
#include <fstream>
#include <string>

class Maps
{
private:
	std::vector<std::string> currentMap;
	float mapWidth;
	float mapHeight;
	sf::Texture tileset;
	sf::Texture background;
public:
	Maps(std::string mapName);
	std::vector<std::string> GetCurrentMap();
	void DrawMap(sf::RenderWindow* window);
};

