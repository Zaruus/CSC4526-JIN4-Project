#include "SlowDownAllStrategy.h"


SlowDownAllStrategy::SlowDownAllStrategy() : AttackStrategy()
{

}

bool SlowDownAllStrategy::attack(std::vector<Enemy*>& targets)
{
    //Inflige 0.5 points de dégats à la première cible disponible

    if (!targets.empty())
    {
        for (int i = 0; i < targets.size(); i++)
        {
            /*if (targets[0]->attack(0.5) < 0)
            {
                return true;
            }*/
          //targets[i]->setSpeed(targets[i]->getOriginSpeed() / 2);
            if (targets[i]->getSpeed() == targets[i]->getOriginSpeed())
            {
                targets[i]->setSpeed(targets[i]->getOriginSpeed()/2);
                targets[i]->reloadMovement();
            }
            

        }
        

    }

    return false;
}