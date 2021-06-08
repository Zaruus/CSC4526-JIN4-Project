#pragma once
#include "Enemy.h"


class AttackStrategy
{
public :
	AttackStrategy();
	virtual void attack(std::vector<std::unique_ptr<Enemy>>& targets) = 0;

};