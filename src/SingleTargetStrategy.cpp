#include "SingleTargetStrategy.h"



SingleTargetStrategy::SingleTargetStrategy() : AttackStrategy()
{

}

bool SingleTargetStrategy::attack(std::vector<Enemy*>& targets)
{
   //Inflige 0.5 points de dégats à la première cible disponible

    if (!targets.empty())
    {
        if (targets[0]->attack(0.5) < 0)
        {
            return true;
        }
       
    }

    return false;
}