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
enum class States { Initial, MOVING, Final };
enum class Triggers { A, B };


//using F = FSM::Fsm<States, States::Initial, Triggers>;

/*const std::vector<F::Trans> transitions =
{
	// from state     , to state      , trigger, guard           , action
	{ States::Initial , States::MOVING     , Triggers::A    , nullptr         , {} },
	{ States::MOVING       , States::Final , Triggers::B    ,nullptr , {} },
};*/


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





private:

	sf::Vector2f coordinates;

	sf::Vector2f movement;
	MoveDirection direction;
	sf::Vector2f size;

	float speed;

	//std::unique_ptr<FSM::Fsm<States, States::Initial, Triggers>> machine;
	FSM::Fsm<States, States::Initial, Triggers> machine;
	sf::RectangleShape image;
	
	//std::unique_ptr<sf::RectangleShape> images = std::make_unique<sf::RectangleShape>(size);

	//sf::RectangleShape* image;

	//std::vector<std::unique_ptr<sf::RectangleShape>> images;



};



