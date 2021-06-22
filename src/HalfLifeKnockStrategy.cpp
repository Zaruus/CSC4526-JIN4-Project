#include "HalfLifeKnock.h"


HalfLifeKnockStrategy::HalfLifeKnockStrategy()
{
	hasKnockedOnce = false;
	deltaKnock = 5;
	//timeUntilKnock = std::chrono::time_poin;
}

float HalfLifeKnockStrategy::knock(std::chrono::time_point<std::chrono::high_resolution_clock> time)
{
	if (hasKnockedOnce)
	{
		//Processus normal
		if (time > timeUntilKnock)
		{

			timeUntilKnock = time + std::chrono::seconds(deltaKnock);
			return 50;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		hasKnockedOnce = true;
		timeUntilKnock = time + std::chrono::seconds(deltaKnock);

		return 0;
	}
}

