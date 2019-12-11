#include "GamePerson.h"

GamePerson::GamePerson(sf::Texture& playerTexture, int x, int y)
{
	this->width = player_width;
	this->height = player_height;
	rect = sf::FloatRect(x, y, width, height);
	sprite.setTexture(playerTexture);
	dx = dy = 0;
	currentFrame = 0;
	sitting = false;
	direction = direction_right;
	life = true;
}

void GamePerson::Sit()
{
	if (!sitting && life)
	{
		sitting = true;
		this->dx = 0;
		rect = sf::FloatRect(rect.left, rect.top, width, height / 2);
	}
}

void GamePerson::Up()
{
	if (sitting && life)
	{
		sitting = false;
		rect = sf::FloatRect(rect.left, rect.top, width, height);
	}
}

void GamePerson::Run(float dx)
{
	if (!sitting && life)
	{
		this->dx = dx;
		direction = dx > 0 ? direction_right : direction_left;
	}
}

void GamePerson::Jump(float dy = player_jump_speed)
{
	if (!sitting && onGround && life)
	{
		onGround = false;
		this->dy = dy;
	}
}

void GamePerson::Die()
{
	rect.width = player_die_width;
	rect.height = player_die_height;
	life = false;
}



void GamePerson::Collision(bool flag, std::vector<std::string> map)
{
	if (rect.left < 0 || rect.left > window_width || rect.top < 0 || rect.top > window_height) return;
	for (int i = rect.top / block_size; i < (rect.top + rect.height) / block_size; i++)
		for (int j = rect.left / block_size; j < (rect.left + rect.width) / block_size; j++)
		{
			char currentElem = map[i][j];
			if (currentElem == block_ground || currentElem == block_ground_grass)
			{
				if (dx > 0 && flag) rect.left = j * block_size - rect.width;
				else if (dx < 0 && flag) rect.left = j * block_size + block_size;
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

void GamePerson::Animation(float time)
{
	currentFrame += player_animation_speed * time;
	if (currentFrame > player_amount_animation) currentFrame -= player_amount_animation;
	if (dx > 0) sprite.setTextureRect(sf::IntRect(width * (int)currentFrame + width, player_texture_y, -width, height));
	if (dx < 0) sprite.setTextureRect(sf::IntRect(width * (int)currentFrame, player_texture_y, width, height));
	if (sitting)
	{
		if (direction == direction_left) sprite.setTextureRect(sf::IntRect(player_texture_x, 225, 55, 21));
		if (direction == direction_right) sprite.setTextureRect(sf::IntRect(player_texture_x + 55, 225, -55, 21));
	}
	if (dx == 0 && !sitting)
	{
		if (direction == direction_left) sprite.setTextureRect(sf::IntRect(player_texture_x, player_texture_y, width, height));
		if (direction == direction_right) sprite.setTextureRect(sf::IntRect(player_texture_x + width, player_texture_y, -width, height));
	}
}

void GamePerson::Update(float time, std::vector<std::string> map, sf::RenderWindow* window)
{
	rect.left += dx * time;
	Collision(true, map); //Collision X
	if (!onGround) dy = dy + gravitation * time;
	rect.top += dy * time;
	onGround = false;
	Collision(false, map); // Collision Y
	if(life) Animation(time);
	else
		sprite.setTextureRect(sf::IntRect(player_texture_die_x, player_texture_die_y, player_die_width, player_die_height));
	sprite.setPosition(rect.left, rect.top);
	dx = 0;
	window->draw(sprite);
}
