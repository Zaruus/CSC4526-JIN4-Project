#pragma once
#include "ResponseStrategy.h"


class BreakResponseStrategy : public ResponseStrategy
{
public:
	BreakResponseStrategy();
	virtual bool respond() override;

};