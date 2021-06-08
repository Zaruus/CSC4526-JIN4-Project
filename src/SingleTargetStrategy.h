#pragma once
#include "AttackStrategy.h"


class SingleTargetStrategy : public AttackStrategy
{
public:
	SingleTargetStrategy();
	virtual bool attack(std::vector<Enemy*>& targets) override;

};