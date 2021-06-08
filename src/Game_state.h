#pragma once

#include<string>

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <chrono>

class Game_state
{
public:
	virtual void update(std::chrono::time_point<std::chrono::high_resolution_clock> time_start) = 0;
	virtual void render(sf::RenderWindow& window) = 0;
	virtual void init() = 0;
	Game_state();

private:



};