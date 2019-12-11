#pragma once
#include "Enemy.h"
#include "GamePerson.h"
#include "Maps.h"
#include "Bullet.h"
#include "MovingPlatform.h"
#include <list>

class GameManager
{
private:
	std::list<GameObject*> objects;
	std::list<GameObject*>::iterator objectsIt;
	bool gameOver;
	bool isMenu;
	int menuNum;
	sf::RenderWindow* window;
public:
	GameManager();
	void StartGame();
	void StartMenu();
};


