#include "GameObject.h"

int GameObject::GetDirection()
{
	return direction;
}
sf::FloatRect GameObject::GetRect()
{
	return rect;
}
void GameObject::Die()
{
	life = false;
}
bool GameObject::isDie()
{
	return !life;
}
sf::FloatRect* GameObject::ChangeRect()
{
	return &rect;
}

int GameObject::Player()
{
	return currentPlayer;
}
