#pragma once
#include "AttackStrategy.h"


class SlowDownAllStrategy : public AttackStrategy
{
public:
	SlowDownAllStrategy();
	virtual bool attack(std::vector<Enemy*>& targets) override;

};