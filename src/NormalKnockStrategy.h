#pragma once
#include "KnockStrategy.h"


class NormalKnockStrategy : public KnockStrategy
{
public:
	NormalKnockStrategy();
	virtual float knock(std::chrono::time_point<std::chrono::high_resolution_clock> time) override;

};