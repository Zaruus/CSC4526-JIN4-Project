#pragma once

#include "fsm.h"
#include "KnockStrategy.h"
#include "NormalKnockStrategy.h"
#include "HalfLifeKnock.h"
#include <iostream>


#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>





enum MoveDirection { UP, DOWN, LEFT, RIGHT, STOPPED };
enum class States { Initial, MOVING,Knocking, Final,Dead };
enum class Triggers { InitialToMoving, MovingToFinal,MovingToDead,FinalToDead, InitialToDead,MovingToKnocking,KnockingToDead};
enum class KnockStrategies {NormalKnock,HalfLifeKnock,last};





class Enemy
{
public:

	Enemy(float x, float y, float width, float height,KnockStrategies strat);

	



	

	void move();

	void update();

	void render(sf::RenderTarget& window);

	void setMovement(MoveDirection newDirection);

	States getState();

	void triggerMachine(Triggers trig);

	sf::Vector2f getSize();

	sf::Vector2f getCoordinates() const;

	std::unique_ptr<Enemy> clone(float x,float y, KnockStrategies strat);

	int attack(float damage);

	int getLife();

	MoveDirection getMoveDirection();

	void setSpeed(float s);

	float getOriginSpeed();

	void reloadMovement();

	float getSpeed();

	float knock(std::chrono::time_point<std::chrono::high_resolution_clock> time);


	void prepareForTest();







private:

	sf::Vector2f coordinates;

	sf::Vector2f movement;
	MoveDirection direction;
	sf::Vector2f size;

	float speed;
	float originSpeed;

	
	FSM::Fsm<States, States::Initial, Triggers> machine;
	sf::RectangleShape image;

	float life;
	float maxLife;

	
	sf::Color healthColor;
	
	KnockStrategies idStrategy;
	KnockStrategy* strategy;
	
	



};



