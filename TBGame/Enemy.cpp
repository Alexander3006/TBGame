#include "Enemy.h"

Enemy::Enemy(sf::Texture& enemyTexture, int x, int y, bool fly)
{
	sprite.setTexture(enemyTexture);
	dx = -enemy_speed;
	currentFrame = 0;
	life = true;
	this->fly = fly;
	if (fly)
	{
		width = enemy_fly_width;
		height = enemy_fly_height;
	}
	else
	{
		width = enemy_ground_width;
		height = enemy_ground_height;
	}
	direction = direction_left;
	rect = sf::FloatRect(x, y, width, height);
	name = "Enemy";
}

void Enemy::Update(float time, std::vector<std::string> map, sf::RenderWindow* window)
{
	rect.left += dx * time;
	Collision(true, map); //Collision X
	if (!fly)
	{
		if (!onGround) dy = dy + gravitation * time;
		rect.top += dy * time;
		onGround = false;
		Collision(false, map); // Collision Y
	}
	if (!life)
	{
		if(!fly)
			sprite.setTextureRect(sf::IntRect(enemy_ground_texture_die_x, enemy_ground_texture_die_y, width, height));
		else
			sprite.setTextureRect(sf::IntRect(enemy_fly_texture_die_x, enemy_fly_texture_die_y, width, height));
	}
	if (life)
	{
		Animation(time);
		sprite.setPosition(rect.left, rect.top);
	}
	window->draw(sprite);
}

void Enemy::Collision(bool flag, std::vector<std::string> map)
{
	for (int i = rect.top / block_size; i < (rect.top + rect.height) / block_size; i++)
		for (int j = rect.left / block_size; j < (rect.left + rect.width) / block_size; j++)
		{
			char currentElem = map[i][j];
			if (currentElem == block_ground || currentElem == block_ground_grass)
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
				if (!fly)
				{
					if (dy > 0 && !flag)
					{
						rect.top = i * block_size - rect.height;
						dy = 0;
						onGround = true;
					}
					else if (dy < 0 && !flag)
					{
						rect.top = i * block_size + block_size;
						dy = 0;
					}
				}

			}
		}
}

void Enemy::Animation(float time)
{
	currentFrame += time * enemy_animation_speed;
	if (currentFrame > enemy_amount_animation)
		currentFrame -= enemy_amount_animation;
	
	if (direction == direction_left)
	{
		if(!fly)
			sprite.setTextureRect(sf::IntRect(width * (int)currentFrame, enemy_ground_texture_y, width, height));
		else
			sprite.setTextureRect(sf::IntRect(width * (int)currentFrame, enemy_fly_texture_y, width, height));
	}
	if (direction == direction_right)
	{
		if(!fly)
			sprite.setTextureRect(sf::IntRect(width * (int)currentFrame + width, enemy_ground_texture_y, -width, height));
		else 
			sprite.setTextureRect(sf::IntRect(width * (int)currentFrame + width, enemy_fly_texture_y, -width, height));
	}
}


void Enemy::Die()
{
	life = false;
	dx = 0;
}