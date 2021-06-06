#include "Enemy.h"


Enemy::Enemy(float x, float y)
{
	sf::Vector2f coords(x, y);
	this->coordinates = coords;

	speed = 0.2f;

}

void Enemy::setSpeed(float newSpeed)
{
	speed = newSpeed;
}

void Enemy::move()
{
	this->coordinates += this->movement;
}

void Enemy::setMovement(MoveDirection newDirection)
{

	if (direction != newDirection)
	{
		switch (newDirection)
		{
		case MoveDirection::UP:
			movement.x = 0;
			movement.y = -1;
			break;
		case MoveDirection::DOWN:
			movement.x = 0;
			movement.y = 1;
			break;
		case MoveDirection::LEFT:
			movement.x = -1;
			movement.y = 0;
			break;
		case MoveDirection::RIGHT:
			movement.x = 1;
			movement.y = 0;
			break;
		case MoveDirection::STOPPED:
			movement.x = 0;
			movement.y = 0;
			break;

		default:
			break;
		}

		direction = newDirection;
	}



}

sf::Vector2f Enemy::getCoordinates() const
{
	return this->coordinates;
}