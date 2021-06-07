#pragma once

#include "Enemy.h"





//enum MoveDirection { UP, DOWN, LEFT, RIGHT, STOPPED };
enum class TowerStates { Initial, Aiming,Shooting, Final };
enum class TowerTriggers { A, B,C,D,E };


class Tower
{
public:
	Tower(float x, float y);
	void update();
	void render(sf::RenderTarget& window);
	TowerStates getState();

	void triggerMachine(TowerTriggers trig);

	void aim(std::vector<std::unique_ptr<Enemy>> enemies);
	


private:
	sf::Vector2f coordinates;

	float range;

	
	std::vector<Enemy*> targets;
	sf::RectangleShape image;

	//std::unique_ptr<FSM::Fsm<States, States::Initial, Triggers>> machine;
	FSM::Fsm<TowerStates, TowerStates::Initial, TowerTriggers> machine;
	sf::RectangleShape tower_image;
};