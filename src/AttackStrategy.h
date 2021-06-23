#pragma once
#include "Enemy.h"


class AttackStrategy
{
public :
	AttackStrategy();
	virtual bool attack(std::vector<Enemy*>& targets) = 0;
	void setAttackDamage(float f);
	float getAttackDamage();
private:
	float attackDamage;

};