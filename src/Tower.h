#pragma once

#include "Enemy.h"
#include "AttackStrategy.h"
#include "SingleTargetStrategy.h"





//enum MoveDirection { UP, DOWN, LEFT, RIGHT, STOPPED };
enum class TowerStates { Initial, Aiming,Shooting, Final };
enum class TowerTriggers { A, B,C,D,E };
enum class Strategy { SingleTargetStrategy };


class Tower
{
public:
	Tower(float x, float y, Strategy strat);
	void update(std::vector<std::unique_ptr<Enemy>>& enemies);
	void render(sf::RenderTarget& window);


	TowerStates getState();

	void triggerMachine(TowerTriggers trig);

	void aim(const std::vector<std::unique_ptr<Enemy>>& enemies);

	std::vector<Enemy*> getTargets() const;
	void addTarget(std::unique_ptr<Enemy> e);
	


private:
	sf::Vector2f coordinates;

	float range;

	
	std::vector<Enemy*> targets;
	sf::RectangleShape image;

	//std::unique_ptr<FSM::Fsm<States, States::Initial, Triggers>> machine;
	FSM::Fsm<TowerStates, TowerStates::Initial, TowerTriggers> machine;
	//sf::RectangleShape tower_image;

	AttackStrategy* strategy;
};