#include <gtest/gtest.h>

#include "myMain.h"
#include <chrono>
#include <pugixml.hpp>
#include <imgui.h>
#include <imgui-SFML.h>



#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "Game_state.h"
#include "Play_state.h"

#include "SFMLOrthogonalLayer.h"





TEST(TestTMX, AffichageMap) {
    sf::RenderWindow window(sf::VideoMode(640, 640), "SFML window");
    tmx::Map map;
    map.load("mainLauncher/resources/retest.tmx");
    MapLayer layerZero(map, 0);


    while (window.isOpen())
    {
        // Event processing
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Request for closing the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear the whole window before rendering a new frame
        window.clear();
        // Draw some graphical entities
        window.draw(layerZero);
        // End the current frame and display its contents on screen
        window.display();
    }

}

TEST(TestTMX, CheckSecondLayerTileID)
{
    sf::RenderWindow window(sf::VideoMode(640, 640), "SFML window");
    tmx::Map map;
    map.load("mainLauncher/resources/retest.tmx");
    MapLayer layerZero(map, 0);
    MapLayer layerOne(map, 1);

    tmx::TileLayer::Tile testTile = layerOne.getTile(8, 0);

    EXPECT_EQ(5, testTile.ID);




}

TEST(TestEnemy, testClass)
{
    Enemy e(0, 0);
    e.setSpeed(1);


    e.setMovement(MoveDirection::DOWN);
    e.move();
    e.move();
    e.move();

    EXPECT_EQ(3, e.getCoordinates().y);


}


TEST(TestPairEnemyFsm, testpairage)//On test le fonctionnement qu'aurais une pair fsm/enemy
{
    Enemy e(0, 0);
    e.setSpeed(1);





    //using F = FSM::Fsm<States, States::Initial, Triggers>;




    //F fsm;
    //fsm.add_transitions(transitions);
    //assert(e.is_initial());
    //fsm.execute(Triggers::A);

    e.setMovement(MoveDirection::DOWN);
    e.triggerMachine(Triggers::A);
    e.update();
    e.update();
    e.update();
    e.update();

    
   e.triggerMachine(Triggers::B);

   e.update();
   e.update();
   e.update();
   e.update();


    

    EXPECT_EQ(4, e.getCoordinates().y);

    //fsm.execute(Triggers::B);
    //assert(States::Final == fsm.state());
    //fsm.reset();
    //assert(fsm.is_initial());




}

