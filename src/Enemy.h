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



enum MoveDirection { UP, DOWN, LEFT, RIGHT, STOPPED };


class Enemy
{
public:

	Enemy(float x, float y);

	void knock();

	void setSpeed(float newSpeed);

	void move();

	void setMovement(MoveDirection newDirection);

	sf::Vector2f getCoordinates() const;




private:

	sf::Vector2f coordinates;

	sf::Vector2f movement;
	MoveDirection direction;

	float speed;




};


enum class States { Initial, MOVING, Final };
enum class Triggers { A, B };


using F = FSM::Fsm<States, States::Initial, Triggers>;

const std::vector<F::Trans> transitions =
{
	// from state     , to state      , trigger, guard           , action
	{ States::Initial , States::MOVING     , Triggers::A    , nullptr         , {} },
	{ States::MOVING       , States::Final , Triggers::B    ,nullptr , {} },
}; 
