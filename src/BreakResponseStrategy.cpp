#include "BreakResponseStrategy.h"
#include <iostream>


BreakResponseStrategy::BreakResponseStrategy() : ResponseStrategy()
{

}

bool BreakResponseStrategy::respond()
{
	std::cout << "Trying to respond\n";
	return true;
}