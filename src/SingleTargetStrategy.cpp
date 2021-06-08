#include "SingleTargetStrategy.h"



SingleTargetStrategy::SingleTargetStrategy() : AttackStrategy()
{

}

void SingleTargetStrategy::attack(std::vector<std::unique_ptr<Enemy>>& targets)
{
    while (!targets.empty()) {
        targets[0]->attack(5);
    }
}