#include "NormalKnockStrategy.h"



NormalKnockStrategy::NormalKnockStrategy()
{

}


float NormalKnockStrategy::knock(std::chrono::time_point<std::chrono::high_resolution_clock> time)
{
	return 0.1f;
}