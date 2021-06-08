#pragma once
#include "Enemy.h"


class AttackStrategy
{
public :
	AttackStrategy();
	virtual bool attack(std::vector<Enemy*>& targets) = 0;

};