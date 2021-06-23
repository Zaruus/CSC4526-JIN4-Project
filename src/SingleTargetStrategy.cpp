#include "SingleTargetStrategy.h"



SingleTargetStrategy::SingleTargetStrategy() : AttackStrategy()
{
    setAttackDamage(0.5f);
}

bool SingleTargetStrategy::attack(std::vector<Enemy*>& targets)
{
   //Inflige 0.5 points de d�gats � la premi�re cible disponible

    if (!targets.empty())
    {
        
        if (targets[0]->attack(getAttackDamage()) < 0)
        {
            return true;
        }
        
    }

    return false;
}