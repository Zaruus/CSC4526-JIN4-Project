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




void Tower::aim(const std::vector<std::unique_ptr<Enemy>> &enemies)
{
    //Si l'ennemi est dans la range de la tour, il est ajouté à sa liste de cibles
    for (auto& e : enemies)
    {
        if ((targets.empty() || std::find(targets.begin(), targets.end(), e.get()) == targets.end())
            && sqrt(pow(this->coordinates.x - e->getCoordinates().x, 2) + pow(this->coordinates.y - e->getCoordinates().y, 2)) < range)
        {
            targets.push_back(e.get());
        }
    }

    //Si l'ennemi est trop loin, il sort de la liste des cibles de la tour
    if (!targets.empty())
    {
        for (int i = 0 ; i < targets.size(); i++)
        {
            if (sqrt(pow(this->coordinates.x - targets[i]->getCoordinates().x, 2) + pow(this->coordinates.y - targets[i]->getCoordinates().y, 2)) > range)
            {
                targets.erase(targets.begin() + i);
            }
        }
    }
}

std::vector<Enemy*> Tower::getTargets() const
{
    return this->targets;
}

void Tower::addTarget(std::unique_ptr<Enemy> e)
{
    targets.push_back(e.get());
}
