#include "Tower.h"



Tower::Tower(float x, float y,Strategy strat)
{
	sf::Vector2f coords(x, y);
	this->coordinates = coords;

	sf::Vector2f size(32, 32) ;
	sf::RectangleShape tmp(size);
	image = tmp;
    image.setFillColor(sf::Color::Black);

	range = 100;

    switch (strat)
    {
    case Strategy::SingleTargetStrategy:
        strategy = new SingleTargetStrategy();
    default:
        strategy = new SingleTargetStrategy();
    }

	

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
            std::cout << "added enemy\n";
        }
    }

    //Si l'ennemi est trop loin, il sort de la liste des cibles de la tour
    if (!targets.empty())
    {
        for (int i = 0 ; i < targets.size(); i++)
        {
            if (sqrt(pow(this->coordinates.x - targets[i]->getCoordinates().x, 2) + pow(this->coordinates.y - targets[i]->getCoordinates().y, 2)) > range || targets[i]->getState() == States::Dead)
            {
                targets.erase(targets.begin() + i);
                std::cout << "removed enemy from targets\n";
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

void Tower::update(std::vector<std::unique_ptr<Enemy>>& enemies)
{
    switch (machine.state())
    {
    case TowerStates::Initial:
        machine.execute(TowerTriggers::A);
        break;
    case TowerStates::Aiming:
        if (targets.size() != 0)
        {
            machine.execute(TowerTriggers::B);
        }
        else
        {
            aim(enemies);
            std::cout << "aiming\n";
        }

        break;
    case TowerStates::Shooting:
        if (targets.size() == 0)
        {
            machine.execute(TowerTriggers::C);
        }
        else
        {
            if (strategy->attack(targets))
            {
                machine.execute(TowerTriggers::C);
            }
            std::cout << "attacking\n";
        }
        break;

    case TowerStates::Final:

        break;

    default:

        break;
    }
}


void Tower::render(sf::RenderTarget& window)
{
    sf::Vector2f renderCoords(coordinates.x, coordinates.y);

    image.setPosition(renderCoords);
    window.draw(image);
}