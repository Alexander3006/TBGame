#pragma once
#include "GameObject.h"

class GamePerson: public GameObject
{
private:
	bool sitting;
	void Animation(float) override;
	void Collision(bool, std::vector<std::string>) override;
public:
	bool onGround;
	GamePerson(sf::Texture&, int, int);
	void Update(float, std::vector<std::string>, sf::RenderWindow*) override;
	void Sit();
	void Up();
	void Run(float);
	void Jump(float);
	void Die();
};

