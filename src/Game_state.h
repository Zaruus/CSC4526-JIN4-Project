#pragma once

#include<string>

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class Game_state
{
public:
	virtual void update() = 0;
	virtual void render(sf::RenderWindow& window) = 0;
	virtual void init() = 0;
	Game_state();

private:



};