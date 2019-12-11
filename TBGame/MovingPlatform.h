#pragma once
#include "GameObject.h"

class MovingPlatform : public GameObject
{
private:
	float moveTimer;
	void Collision(bool, std::vector<std::string>) override;
	void Animation(float) override;
public:
	MovingPlatform(sf::Texture&, int, int, int);
	void Update(float, std::vector<std::string>, sf::RenderWindow*) override;
};

