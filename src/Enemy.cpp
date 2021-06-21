#include "Enemy.h"


Enemy::Enemy(float x, float y,float width,float height)
{
	//BreakResponseStrategy tmps();
	//this->strategy = tmps;
	strategy = new BreakResponseStrategy();
	attackedTowers = 2;

	sf::Vector2f coords(x, y);
	this->coordinates = coords;

	originSpeed = 1.0f;
	speed = 1.0f;

	

	machine.add_transitions({
		// from state     , to state      , trigger, guard           , action
		{ States::Initial , States::MOVING     , Triggers::InitialToMoving    , nullptr         , {} },
		{ States::MOVING       , States::Final , Triggers::MovingToFinal    ,nullptr , {} },
		{ States::MOVING       , States::Dead , Triggers::MovingToDead    ,nullptr , {} },
		{ States::Final       , States::Dead , Triggers::FinalToDead    ,nullptr , {} },
		{ States::Initial       , States::Dead , Triggers::InitialToDead    ,nullptr , {} },
		});

	sf::Vector2f size(width,height);
	this->size = size;
	sf::RectangleShape tmp(size);
	tmp.setOrigin(size.x/2, size.x / 2);
	tmp.setPosition(coords);

	image = tmp;

	life = 100;

	
	
	
	

}



void Enemy::move()
{
	this->coordinates += this->movement;
	image.setPosition(image.getPosition() + movement);
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

		reloadMovement();
		direction = newDirection;
	}



}

MoveDirection Enemy::getMoveDirection()
{
	return direction;
}

sf::Vector2f Enemy::getCoordinates() const
{
	//return this->coordinates;
	return image.getPosition();
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
	//std::cout << "My speed is : " << speed << "\n";
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
	//sf::Vector2f renderCoords(coordinates.x,coordinates.y);
	
	//image.setPosition(renderCoords);
	sf::Color health(abs(life)*2.55, 0, 0, 255);
	image.setFillColor(health);
	window.draw(image);

}

sf::Vector2f Enemy::getSize()
{
	return this->size;
}

std::unique_ptr<Enemy> Enemy::clone(float x,float y)
{
	auto tmp = std::make_unique<Enemy>(x, y, this->size.x, this->size.y);
	

	return std::move(tmp);
}

int Enemy::attack(float damage)
{
	//On enlève de la vie à l'instance et on la passe en State::Dead via un trigger si besoin
	life -= damage;
	if (life <= 0)
	{
		switch (machine.state())
		{
		case States::Initial :
			machine.execute(Triggers::InitialToDead);
			break;

		case States::MOVING:
			machine.execute(Triggers::MovingToDead);
			break;

		case States::Final:
			machine.execute(Triggers::FinalToDead);
			break;
		}

	
	}
	return life;
}

int Enemy::getLife()
{
	return this->life;
}

void Enemy::setSpeed(float s)
{
	speed = s;
}

float Enemy::getOriginSpeed()
{
	return originSpeed;
}

void Enemy::reloadMovement()
{

	float l = sqrt(pow(movement.x, 2) + pow(movement.y, 2));
	movement = movement * (1.0f/l);

	movement = movement * speed;
	
}

float Enemy::getSpeed()
{
	return speed;
}


void Enemy::respond()
{
	if (attackedTowers > 0)
	{
		if (strategy->respond())
		{
			attackedTowers--;
		}
	}
	//strategy->respond();
}