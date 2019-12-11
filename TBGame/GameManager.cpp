#include "GameManager.h"
using namespace sf;

GameManager::GameManager()
{
	window = new RenderWindow(VideoMode(window_width, window_height), "TBGame");
	isMenu = true;
	gameOver = true;
}

void GameManager::StartGame()
{
	Clock* clock = new Clock();

	//load Texture
	Texture* enemyTexture = new Texture();
	enemyTexture->loadFromFile("./Texture/enemy.png");

	Texture* playerTexture1 = new Texture();
	playerTexture1->loadFromFile("./Texture/hero.gif");

	Texture* playerTexture2 = new Texture();
	playerTexture2->loadFromFile("./Texture/hero.gif");

	Texture* bulletTexture = new Texture();
	bulletTexture->loadFromFile("./Texture/bullet.png");


	Texture* tileset = new Texture();
	tileset->loadFromFile("./Maps/map1/tileset.png");

	Texture* win1Texture = new Texture();
	win1Texture->loadFromFile("./Texture/player1Win.png");

	Texture* win2Texture = new Texture();
	win2Texture->loadFromFile("./Texture/player2Win.png");

	Sprite* playerWin;
	

	//createMap
	Maps* map = new Maps("map1");

	//create personage
	GamePerson* player1 = new GamePerson(*playerTexture1, player1_start_position_x, player1_start_position_y);
	GamePerson* player2 = new GamePerson(*playerTexture2, player2_start_position_x, player2_start_position_y);

	//create enemy
	objects.push_back(new Enemy(*enemyTexture, 400, 200, true));
	objects.push_back(new Enemy(*enemyTexture, 350, 150, true));
	objects.push_back(new Enemy(*enemyTexture, 200, 200, false));
	objects.push_back(new Enemy(*enemyTexture, 200, 800, false));
	objects.push_back(new Enemy(*enemyTexture, 960, 256, false));

	//create moving platform
	objects.push_back(new MovingPlatform(*tileset, 256, 256, 128));
	objects.push_back(new MovingPlatform(*tileset, 352, 352, 128));


	window->setKeyRepeatEnabled(false);

	//Start game loop
	while (window->isOpen() && !gameOver)
	{
		float time = clock->getElapsedTime().asMilliseconds();
		clock->restart();

		//Keyboard input
		Event event;
		while (window->pollEvent(event))
		{	
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::RShift)
				{
					if (player1->isDie() == false)
					{
						objects.push_back(new Bullet(*bulletTexture, player1->GetRect().left, player1->GetRect().top, player1->GetDirection(), isPlayer1));
					}
				}
				if (event.key.code == Keyboard::Tab)
				{
					if (player2->isDie() == false)
					{
						objects.push_back(new Bullet(*bulletTexture, player2->GetRect().left, player2->GetRect().top, player2->GetDirection(), isPlayer2));
					}
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			player1->Run(player_run_speed);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			player1->Run(-player_run_speed);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			player1->Up();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			player1->Sit();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
		{
			player1->Jump(player_jump_speed);
		}
		///////player2
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			player2->Run(-player_run_speed);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			player2->Run(player_run_speed);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			player2->Up();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			player2->Sit();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
		{
			player2->Jump(player_jump_speed);
		}
		if (sf::Keyboard::isKeyPressed(Keyboard::Escape))
		{
			gameOver = true;
			isMenu = true;
			objects.clear();
			delete player1;
			delete player2;
			delete map;
			delete bulletTexture, playerTexture1, playerTexture2, enemyTexture;
			delete win1Texture, win2Texture, playerWin;
			delete clock;
			StartMenu();
			return;
		}

		//logic yourself collision
		for (objectsIt = objects.begin(); objectsIt != objects.end(); objectsIt++)
		{
			if ((*objectsIt)->name == "Enemy")
			{
				GameObject* enemy = *objectsIt;
				if (enemy->isDie() == true) continue;
				for (std::list<GameObject*>::iterator objectsIt2 = objects.begin(); objectsIt2 != objects.end(); objectsIt2++)
				{
					GameObject* bullet = *objectsIt2;
					if (bullet->name == "Bullet" && bullet->isDie() == false)
					{
						if (bullet->GetRect().intersects(enemy->GetRect()))
						{
							enemy->Die();
							bullet->Die();
						}
					}
				}
			}

			if ((*objectsIt)->name == "Enemy" && (*objectsIt)->isDie() == false)
			{
				if ((*objectsIt)->GetRect().intersects(player1->GetRect()))
					player1->Die();
				if ((*objectsIt)->GetRect().intersects(player2->GetRect()))
					player2->Die();
			}

			if ((*objectsIt)->name == "Bullet" && (*objectsIt)->isDie() == false)
			{
				if ((*objectsIt)->GetRect().intersects(player1->GetRect()) && (*objectsIt)->Player() != isPlayer1)
					player1->Die();
				if ((*objectsIt)->GetRect().intersects(player2->GetRect()) && (*objectsIt)->Player() != isPlayer2)
					player2->Die();
			}

			if (((*objectsIt)->name == "MovingPlatform") && ((*objectsIt)->GetRect().intersects(player1->GetRect())))
			{
				if ((player1->dy > 0) || (player1->onGround == false))
				{
					if (player1->GetRect().top + player1->GetRect().height < (*objectsIt)->GetRect().top + (*objectsIt)->GetRect().height)
					{
						player1->ChangeRect()->top = (*objectsIt)->GetRect().top - player1->GetRect().height;
						player1->ChangeRect()->left += (*objectsIt)->dx * time;
						player1->onGround = true;
					}
				}
			}

			if (((*objectsIt)->name == "MovingPlatform") && ((*objectsIt)->GetRect().intersects(player2->GetRect())))
			{
				if ((player2->dy > 0) || (player2->onGround == false))
				{
					if (player2->GetRect().top + player2->GetRect().height < (*objectsIt)->GetRect().top + (*objectsIt)->GetRect().height)
					{
						player2->ChangeRect()->top = (*objectsIt)->GetRect().top - player2->GetRect().height;
						player2->ChangeRect()->left += (*objectsIt)->dx * time;
						player2->onGround = true;
					}
				}
			}
		}

		

		window->clear();
		if(!gameOver) map->DrawMap(window);

		//object manage and draw
		for (objectsIt = objects.begin(); objectsIt != objects.end(); objectsIt++)
			(*objectsIt)->Update(time, map->GetCurrentMap(), window);
		for (objectsIt = objects.begin(); objectsIt != objects.end(); objectsIt++)
		{
			if ((*objectsIt)->isDie() == true && (*objectsIt)->name != "Enemy")
			{
				objectsIt = objects.erase(objectsIt);
			}
		}

		player1->Update(time, map->GetCurrentMap(), window);
		player2->Update(time, map->GetCurrentMap(), window);

		if (player1->isDie())
		{
			playerWin = new Sprite(*win1Texture);
			playerWin->setPosition(380, 400);
			window->draw(*playerWin);
		}
		if (player2->isDie())
		{
			playerWin = new Sprite(*win2Texture);
			playerWin->setPosition(380, 400);
			window->draw(*playerWin);
		}

		window->display();

	}
}

void GameManager::StartMenu()
{
	Texture* menuBackground = new Texture();
	Texture* menuStart = new Texture();
	Texture* menuQuit = new Texture();
	
	menuBackground->loadFromFile("./menu/background.jpg");
	menuStart->loadFromFile("./menu/menuStart.png");
	menuQuit->loadFromFile("./menu/menuQuit.png");

	Sprite start(*menuStart), quit(*menuQuit), background(*menuBackground);

	start.setPosition(450, 250);
	quit.setPosition(450, 550);

	while (isMenu || gameOver)
	{
		menuNum = 1;
		window->clear();

		if (IntRect(450, 250, 450, 320).contains(Mouse::getPosition(*window)))
		{
			menuNum = 1;
			quit.setColor(Color(158, 53, 227));
			start.setColor(Color::Green);

		}
		if (IntRect(550, 570, 900, 650).contains(Mouse::getPosition(*window)))
		{
			menuNum = 3;
			start.setColor(Color(158, 53, 227));
			quit.setColor(Color::Green);
		}
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1)
			{
				isMenu = false;
				gameOver = false; 
				delete menuBackground, menuQuit, menuStart;
				StartGame();
			}
			if (menuNum == 3) gameOver = true; isMenu = false;  window->close();
		}
		if (window->isOpen())
		{
			window->draw(background);
			window->draw(start);
			window->draw(quit);
			window->display();
		}

	}
}