#pragma once

#include "Enemy.h"
#include "AttackStrategy.h"
#include "SingleTargetStrategy.h"
#include "SlowDownAllStrategy.h"
#include "ZoneAttackStrategy.h"
#include "SFML/Graphics/CircleShape.hpp"

#include <chrono>





//enum MoveDirection { UP, DOWN, LEFT, RIGHT, STOPPED };
enum class TowerStates { Initial, Aiming,Shooting,Broken, Final };
enum class TowerTriggers { InitialToAiming, AimingToShooting, ShootingToAiming, ShootingToFinal, AimingToFinal,ShootingToBroken,BrokenToAiming};
enum class Strategy { SingleTargetStrategy, SlowDownAllStrategy, ZoneAttackStrategy, last};


class Tower
{
public:
	Tower(float x, float y, Strategy strat);
	void update(std::vector<std::unique_ptr<Enemy>>& enemies, std::chrono::time_point<std::chrono::high_resolution_clock> time);
	void render(sf::RenderTarget& window);


	TowerStates getState();

	void triggerMachine(TowerTriggers trig);

	void aim(const std::vector<std::unique_ptr<Enemy>>& enemies);

	std::vector<Enemy*> getTargets() const;
	double Tower::getDistance(const Enemy& e) const;
	void addTarget(std::unique_ptr<Enemy> e);

	sf::Vector2f getCoordinates();

	std::unique_ptr<Tower> clone(float x,float y, Strategy strat);

	void breakDown();
	


private:
	sf::Vector2f coordinates;

	float range;

	
	std::vector<Enemy*> targets;
	sf::RectangleShape image;

	FSM::Fsm<TowerStates, TowerStates::Initial, TowerTriggers> machine;

	AttackStrategy* strategy;
	Strategy idStrategy;
	sf::CircleShape rangeCircle;



	int brokenDownTime;
	bool hasBrokenDown;
	std::chrono::time_point<std::chrono::high_resolution_clock> timeUntilRepair;
};