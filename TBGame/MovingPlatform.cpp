#include "MovingPlatform.h"

MovingPlatform::MovingPlatform(sf::Texture& texture, int x, int y, int width)
{
	sprite.setTexture(texture);
	life = true;
	direction = direction_right;
	dx = platform_speed;
	this->width = width;
	this->height = block_size;
	rect = sf::FloatRect(x, y, width, block_size);
	name = "MovingPlatform";
	moveTimer = 0;
}

void MovingPlatform::Collision(bool flag, std::vector<std::string> map)
{
	if (flag)
	{
		for (int i = rect.top / block_size; i < (rect.top + rect.height) / block_size; i++)
			for (int j = rect.left / block_size; j < (rect.left + rect.width) / block_size; j++)
			{
				char currentElem = map[i][j];
				if (currentElem == block_ground || currentElem == block_ground_grass)
				{
					{
						if (dx > 0 && flag)
						{
							rect.left = j * block_size - rect.width;
							direction = direction_left;
							dx *= -1;
						}
						else if (dx < 0 && flag)
						{
							dx *= -1;
							rect.left = j * block_size + block_size;
							direction = direction_right;
						}
					}
				}
			}
	}

	if (moveTimer > 6000)
	{
		dx *= -1;
		direction *= -1;
		moveTimer = 0;
	}
	
}

void MovingPlatform::Animation(float)
{
	sprite.setTextureRect(sf::IntRect(platform_texture_x, platform_texture_y, block_size + 1, height));
}


void MovingPlatform::Update(float time, std::vector<std::string> map, sf::RenderWindow* window)
{
	rect.left += dx * time;
	Collision(true, map);
	moveTimer += time;
	Collision(false, map);
	Animation(time);
	for (int i = 0; i < width / block_size; i++)
	{
		sprite.setPosition(rect.left + i * block_size, rect.top);
		window->draw(sprite);
	}
}
