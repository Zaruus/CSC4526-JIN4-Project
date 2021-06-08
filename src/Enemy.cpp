#include "Enemy.h"


Enemy::Enemy(float x, float y,float width,float height)
{
	sf::Vector2f coords(x, y);
	this->coordinates = coords;

	speed = 0.2f;

	//machine = std::make_unique<FSM::Fsm<States, States::Initial, Triggers>>();

	machine.add_transitions({
		// from state     , to state      , trigger, guard           , action
		{ States::Initial , States::MOVING     , Triggers::A    , nullptr         , {} },
		{ States::MOVING       , States::Final , Triggers::B    ,nullptr , {} },
		{ States::MOVING       , States::Dead , Triggers::C    ,nullptr , {} },
		{ States::Final       , States::Dead , Triggers::D    ,nullptr , {} },
		{ States::Initial       , States::Dead , Triggers::E    ,nullptr , {} },
		});

	sf::Vector2f size(width,height);
	this->size = size;
	sf::RectangleShape tmp(size);

	image = tmp;

	life = 100;

	
	//this->image->setSize(size);
	
	

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

States Enemy::getState()
{
	return this->machine.state();
}

void Enemy::triggerMachine(Triggers trig)
{
	this->machine.execute(trig);
}

void Enemy::update()
{
	switch (machine.state())
	{
	case States::MOVING:
		move();
		break;

	default:

		break;
	}
}


void Enemy::render(sf::RenderTarget& window)
{
	sf::Vector2f renderCoords(coordinates.x-size.x/2,coordinates.y-size.y/2);
	
	image.setPosition(renderCoords);
	window.draw(image);

}

sf::Vector2f Enemy::getSize()
{
	return this->size;
}

Enemy Enemy::clone(float x,float y)
{
	Enemy clone(x, y, this->size.x, this->size.y);

	return clone;
}

int Enemy::attack(int damage)
{
	life -= damage;
	if (life <= 0)
	{
		switch (machine.state())
		{
		case States::Initial :
			machine.execute(Triggers::E);
			break;

		case States::MOVING:
			machine.execute(Triggers::C);
			break;

		case States::Final:
			machine.execute(Triggers::D);
			break;
		}

	
	}
	return life;
}

int Enemy::getLife()
{
	return this->life;
}