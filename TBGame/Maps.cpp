#include "Maps.h"


Maps::Maps(std::string mapName)
{
	std::string currentline;
	std::ifstream file("./Maps/" + mapName + "/map.txt");
	while (std::getline(file, currentline))
	{
		int i = 0;
		currentMap.push_back(currentline);
		i++;
	}
	file.close();
	tileset.loadFromFile("./Maps/" + mapName + "/tileset.png");
	background.loadFromFile("./Maps/" + mapName + "/background.png");
	mapHeight = window_height / block_size;
	mapWidth = window_width / block_size;
}

std::vector<std::string> Maps::GetCurrentMap()
{
	return currentMap;
}

void Maps::DrawMap(sf::RenderWindow* window)
{
	sf::Sprite background;
	background.setTexture(this->background);
	window->draw(background);
	sf::Sprite block;
	block.setTexture(tileset);
	for (int i = 0; i < mapHeight; i++)
		for (int j = 0; j < mapWidth; j++)
		{
			char currentElem = currentMap[i][j];
			if (currentElem == block_ground_grass)
				block.setTextureRect(sf::IntRect(texture_ground_gress_x, texture_ground_gress_y, texture_block_size, texture_block_size));
			if (currentElem == block_ground)
				block.setTextureRect(sf::IntRect(texture_ground_x, texture_ground_y, texture_block_size, texture_block_size));
			if (currentElem == block_no) continue;
				block.setPosition(j * block_size, i * block_size);
			window->draw(block);
		}
}