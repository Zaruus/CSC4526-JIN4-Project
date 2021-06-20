#pragma once
#include "AttackStrategy.h"

class ZoneAttackStrategy : public AttackStrategy
{
public:
	ZoneAttackStrategy();
	virtual bool attack(std::vector<Enemy*>& targets) override;

};