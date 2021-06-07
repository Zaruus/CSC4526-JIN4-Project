#include "Tower.h"


Tower::Tower(float x, float y)
{
	sf::Vector2f coords(x, y);
	this->coordinates = coords;

	sf::Vector2f size(20, 20) ;
	sf::RectangleShape tmp(size);
	tower_image = tmp;

	range = 100;

	

	//machine = std::make_unique<FSM::Fsm<States, States::Initial, Triggers>>();

	machine.add_transitions({
		// from state     , to state      , trigger, guard           , action
		{ TowerStates::Initial , TowerStates::Aiming     , TowerTriggers::A    , nullptr         , {} },
		{ TowerStates::Aiming       , TowerStates::Shooting , TowerTriggers::B    ,nullptr , {} },
		{ TowerStates::Shooting       , TowerStates::Aiming , TowerTriggers::C    ,nullptr , {} },
		{ TowerStates::Shooting       , TowerStates::Final , TowerTriggers::D    ,nullptr , {} },
		{ TowerStates::Aiming       , TowerStates::Final , TowerTriggers::E    ,nullptr , {} },
		});
}

TowerStates Tower::getState()
{
	return machine.state();
}

void Tower::triggerMachine(TowerTriggers trig)
{
	machine.execute(trig);
}

void Tower::aim(std::vector<std::unique_ptr<Enemy>> enemies)
{
	if (targets.size() != 0)
	{
		for (int i =0;i<targets.size();i++)
		{
			if (abs(sqrt((this->coordinates.x - targets[i]->getCoordinates().x) * (this->coordinates.x - targets[i]->getCoordinates().x) + (this->coordinates.y - targets[i]->getCoordinates().y) * (this->coordinates.y - targets[i]->getCoordinates().y))) > 0)
			{
				targets.erase(targets.begin() + i);
			}
		}
	}
	



	for (auto e = enemies.begin(); e != enemies.end(); e++)
	{

	}
}