#include "Bullet.h"

Bullet::Bullet(sf::Texture& bulletTexture, int x, int y, int direction, int player)
{
	sprite.setTexture(bulletTexture);
	this->direction = direction;
	width = bullet_width;
	height = bullet_height;
	if (direction == direction_left)
	{
		dx = -bullet_speed;
		rect = sf::FloatRect(x - player_width/2, y, width, height);
	}
	else
	{
		dx = bullet_speed;
		rect = sf::FloatRect(x + player_width, y, width, height);
	}
	currentFrame = 0;
	life = true;
	name = "Bullet";
	currentPlayer = player;
}

void Bullet::Update(float time, std::vector<std::string> map, sf::RenderWindow* window)
{
		rect.left += dx * time;
		Collision(true, map);
		Animation(time);
		sprite.setPosition(rect.left, rect.top);
		if(life)
			window->draw(sprite);
}

void Bullet::Collision(bool flag, std::vector<std::string> map)
{
	for (int i = rect.top / block_size; i < (rect.top + rect.height) / block_size; i++)
		for (int j = rect.left / block_size; j < (rect.left + rect.width) / block_size; j++)
		{
			char currentElem = map[i][j];
			if (currentElem == block_ground || currentElem == block_ground_grass)
			{
				life = false;
				dx = 0;
			}
		}
}

void Bullet::Animation(float time)
{
	currentFrame += time * bullet_animation_speed;
	if (currentFrame > bullet_amount_animation)
		currentFrame -= bullet_amount_animation;
	if (direction == direction_right)
		sprite.setTextureRect(sf::IntRect(width * (int)currentFrame, bullet_texture_y, width, height));
	if (direction == direction_left)
		sprite.setTextureRect(sf::IntRect(width * (int)currentFrame + width, bullet_texture_y, -width, height));
}
