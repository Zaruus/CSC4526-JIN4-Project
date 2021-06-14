#pragma once

#include "fsm.h"
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
enum class States { Initial, MOVING, Final,Dead };
enum class Triggers { InitialToMoving, MovingToFinal,MovingToDead,FinalToDead, InitialToDead};





class Enemy
{
public:

	Enemy(float x, float y, float width, float height);

	

	void knock();

	void setSpeed(float newSpeed);

	void move();

	void update();

	void render(sf::RenderTarget& window);

	void setMovement(MoveDirection newDirection);

	States getState();

	void triggerMachine(Triggers trig);

	sf::Vector2f getSize();

	sf::Vector2f getCoordinates() const;

	std::unique_ptr<Enemy> clone(float x,float y);

	int attack(float damage);

	int getLife();

	MoveDirection getMoveDirection();





private:

	sf::Vector2f coordinates;

	sf::Vector2f movement;
	MoveDirection direction;
	sf::Vector2f size;

	float speed;

	
	FSM::Fsm<States, States::Initial, Triggers> machine;
	sf::RectangleShape image;

	float life;
	
	



};



