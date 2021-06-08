#include "SingleTargetStrategy.h"



SingleTargetStrategy::SingleTargetStrategy() : AttackStrategy()
{

}

bool SingleTargetStrategy::attack(std::vector<Enemy*>& targets)
{
    /*while (!targets.empty()) {
        targets[0]->attack(5);
    }*/

    if (!targets.empty())
    {
        if (targets[0]->attack(5) < 0)
        {
            return true;
        }
       
    }

    return false;
}