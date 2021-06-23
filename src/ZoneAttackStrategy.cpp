#include "ZoneAttackStrategy.h"



ZoneAttackStrategy::ZoneAttackStrategy() : AttackStrategy()
{
    setAttackDamage(0.3f);
}

bool ZoneAttackStrategy::attack(std::vector<Enemy*>& targets)
{
    //Inflige 0.3 points de dégats à toutes les cibles disponibles

    if (!targets.empty())
    {
        for (auto target : targets) {
            if (target->attack(getAttackDamage()) < 0) {
                return true;
            }
        }
    }

    return false;
}