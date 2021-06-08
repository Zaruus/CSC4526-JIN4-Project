#pragma once
#include "AttackStrategy.h"


class SingleTargetStrategy : public AttackStrategy
{
public:
	SingleTargetStrategy();
	virtual void attack(std::vector<std::unique_ptr<Enemy>> targets) override;

};