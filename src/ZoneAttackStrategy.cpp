#include "ZoneAttackStrategy.h"



ZoneAttackStrategy::ZoneAttackStrategy() : AttackStrategy()
{

}

bool ZoneAttackStrategy::attack(std::vector<Enemy*>& targets)
{
    //Inflige 0.3 points de dégats à toutes les cibles disponibles

    if (!targets.empty())
    {
        for (auto target : targets) {
            if (target->attack(0.3) < 0) {
                return true;
            }
        }
    }

    return false;
}