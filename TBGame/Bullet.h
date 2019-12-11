#pragma once
#include "GameObject.h"

class Bullet: public GameObject
{
private:
	void Collision(bool, std::vector<std::string>) override;
	void Animation(float) override;
public:
	Bullet(sf::Texture&, int, int, int, int);
	void Update(float, std::vector<std::string>, sf::RenderWindow*);
};

