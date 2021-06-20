#include "Tower.h"



Tower::Tower(float x, float y,Strategy strat)
{

	sf::Vector2f coords(x, y);
	this->coordinates = coords;

	sf::Vector2f size(32, 32) ;
	sf::RectangleShape tmp(size);
    

	
    

	range = 100;

    sf::CircleShape tmpc(range,20);
    tmpc.setFillColor(sf::Color::Transparent);
    tmpc.setOutlineThickness(2);
    tmpc.setOutlineColor(sf::Color::Blue);
    tmpc.setOrigin(range, range);

    rangeCircle = tmpc;

    idStrategy = strat;

    switch (strat)
    {
    case Strategy::SingleTargetStrategy:
        strategy = new SingleTargetStrategy();
        tmp.setFillColor(sf::Color::Black);
        break;

    case Strategy::SlowDownAllStrategy:
        strategy = new SlowDownAllStrategy();
        tmp.setFillColor(sf::Color::Blue);
        break;
    default:
        strategy = new SingleTargetStrategy();
        tmp.setFillColor(sf::Color::Black);
        break;
    }
    
    image = tmp;

	

	

	machine.add_transitions({
		// from state     , to state      , trigger, guard           , action
		{ TowerStates::Initial , TowerStates::Aiming     , TowerTriggers::InitialToAiming    , nullptr         , {} },
		{ TowerStates::Aiming       , TowerStates::Shooting , TowerTriggers::AimingToShooting    ,nullptr , {} },
		{ TowerStates::Shooting       , TowerStates::Aiming , TowerTriggers::ShootingToAiming    ,nullptr , {} },
		{ TowerStates::Shooting       , TowerStates::Final , TowerTriggers::ShootingToFinal    ,nullptr , {} },
		{ TowerStates::Aiming       , TowerStates::Final , TowerTriggers::AimingToFinal    ,nullptr , {} },
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
            && this->getDistance(*e) < pow(range,2))
        {
            targets.push_back(e.get());
            
        }
    }

    for (int i = 0; i < targets.size(); i++)
    {
        if (this->getDistance(*targets[i]) > pow(range, 2) || targets[i]->getState() == States::Dead)
        {

            switch (idStrategy)
            {
            case Strategy::SingleTargetStrategy:
                //Nothing to do here
                break;
                
            case Strategy::SlowDownAllStrategy:
                targets[i]->setSpeed(targets[i]->getOriginSpeed());
                
                targets[i]->reloadMovement();
                break;
            default:

                break;
            }
            targets.erase(targets.begin() + i);

        }
    }
}

std::vector<Enemy*> Tower::getTargets() const
{
    return this->targets;
}

double Tower::getDistance(const Enemy& e) const
{
    return pow(this->coordinates.x - e.getCoordinates().x, 2) + pow(this->coordinates.y - e.getCoordinates().y, 2);
}

void Tower::addTarget(std::unique_ptr<Enemy> e)
{
    targets.push_back(e.get());
}

void Tower::update(std::vector<std::unique_ptr<Enemy>>& enemies)
{
    //std::cout << "Tower targets size is : " << targets.size() << "\n";
    switch (machine.state())
    {
    case TowerStates::Initial:
        machine.execute(TowerTriggers::InitialToAiming);
        break;
    case TowerStates::Aiming:
        if (targets.size() != 0)
        {
            machine.execute(TowerTriggers::AimingToShooting);
        }
        else
        {
            aim(enemies);
            
        }

        break;
    case TowerStates::Shooting:
        if (targets.size() == 0)
        {
            machine.execute(TowerTriggers::ShootingToAiming);
        }
        else
        {
            //Si l'ennemi est trop loin, il sort de la liste des cibles de la tour
            /*if (!targets.empty())
            {
                for (int i = 0; i < targets.size(); i++)
                {
                    if (this->getDistance(*targets[i]) > pow(range, 2) || targets[i]->getState() == States::Dead)
                    {
                        targets.erase(targets.begin() + i);

                    }
                }
            }*/
            

           /* if (strategy->attack(targets))
            {
                machine.execute(TowerTriggers::ShootingToAiming);
                targets.erase(targets.begin());
               
            }*/
            bool resultAttack = strategy->attack(targets);
            switch (idStrategy)
            {
            case Strategy::SingleTargetStrategy:

                break;
                if (resultAttack)
                {
                    targets.erase(targets.begin());
                }
            case Strategy::SlowDownAllStrategy:
             /*for (int i = 0; i < targets.size(); i++)
                {
                    targets[i]->setSpeed(targets[i]->getOriginSpeed());
                }*/
                break;
            default:

                break;
            }


            aim(enemies);
            
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
    sf::Vector2f renderCoords2(coordinates.x+16, coordinates.y+16);
    

    image.setPosition(renderCoords);
    rangeCircle.setPosition(renderCoords2);
    
    window.draw(image);
    window.draw(rangeCircle);
}

sf::Vector2f Tower::getCoordinates()
{
    return this->coordinates;
}

std::unique_ptr<Tower> Tower::clone(float x,float y, Strategy strat)
{
    //auto newClone = std::make_unique<Tower>(x, y, idStrategy);
    auto newClone = std::make_unique<Tower>(x, y, strat);
    
    return std::move(newClone);
}