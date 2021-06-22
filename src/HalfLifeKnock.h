#pragma once
#include "KnockStrategy.h"
class HalfLifeKnockStrategy : public KnockStrategy
{
public:
	HalfLifeKnockStrategy();
	virtual float knock(std::chrono::time_point<std::chrono::high_resolution_clock> time) override;


private:
	std::chrono::time_point<std::chrono::high_resolution_clock> timeUntilKnock;
	bool hasKnockedOnce;
	int deltaKnock;

};