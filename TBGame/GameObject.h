#pragma once
#include <SFML/Graphics.hpp>
#include "PreprocessConst.h"
#include <string>

class GameObject 
{
private:
protected:
	int width, height;
	float currentFrame;
	int direction;
	sf::FloatRect rect;
	sf::Sprite sprite;
	virtual void Animation(float) = 0;
	virtual void Collision(bool, std::vector<std::string>) = 0;
	bool life;
	int currentPlayer;
public:
	float dx, dy;
	std::string name;
	virtual void Update(float time, std::vector<std::string> map, sf::RenderWindow* window) = 0;
	int GetDirection();
	sf::FloatRect GetRect();
	void Die();
	bool isDie();
	sf::FloatRect* ChangeRect();
	int Player();
};

