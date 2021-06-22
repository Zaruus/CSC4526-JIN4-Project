#include "NormalKnockStrategy.h"
#include <iostream>


NormalKnockStrategy::NormalKnockStrategy()
{

}


float NormalKnockStrategy::knock(std::chrono::time_point<std::chrono::high_resolution_clock> time)
{
	return 0.1f;
}

void NormalKnockStrategy::prepareForTest()
{
	std::cout << "Prepared enemy strategy for test, this should not appear \n";
}