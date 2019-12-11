#pragma once
#include "GameObject.h"

class Enemy: public GameObject
{
private:
	bool fly;
	bool onGround;
	void Collision(bool, std::vector<std::string>);
	void Animation(float);
public:
	Enemy(sf::Texture&, int, int, bool);
	void Update(float, std::vector<std::string>, sf::RenderWindow*);
	void Die();
};

