#pragma once
#include <chrono>




class KnockStrategy
{
public:
	KnockStrategy();
	virtual float knock(std::chrono::time_point<std::chrono::high_resolution_clock> time) = 0;
	virtual void prepareForTest() = 0;
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> time_since_knocked;

};