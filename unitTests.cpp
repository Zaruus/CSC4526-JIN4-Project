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

#include "Tower.h"




TEST(TestTMX, AffichageMap) {
    sf::RenderWindow window(sf::VideoMode(640, 640), "SFML window");
    tmx::Map map;
    map.load("mainlauncher/resources/retest.tmx");
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
    map.load("mainlauncher/resources/retest.tmx");
    MapLayer layerZero(map, 0);
    MapLayer layerOne(map, 1);

    tmx::TileLayer::Tile testTile = layerOne.getTile(8, 0);

    EXPECT_EQ(5, testTile.ID);




}

TEST(TestEnemy, testClass)
{
    Enemy e(0, 0,1,1);
    e.setSpeed(1);


    e.setMovement(MoveDirection::DOWN);
    e.move();
    e.move();
    e.move();

    EXPECT_EQ(3, e.getCoordinates().y);


}


TEST(TestPairEnemyFsm, testpairage)//On test le fonctionnement qu'aurais une pair fsm/enemy
{
    Enemy e(0, 0,1,1);
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

TEST(TestEnemy, testaffichage)
{
    sf::RenderWindow window(sf::VideoMode(640, 640), "SFML window");
    Enemy e(0, 0, 200, 200);
   
    


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
        e.render(window);
        // End the current frame and display its contents on screen
        window.display();
    }
}


TEST(TestTower, testTargets)
{
    Tower* tower = new Tower(0, 0,Strategy::SingleTargetStrategy);
    std::vector<std::unique_ptr<Enemy>> enemies;

    tower->addTarget(std::make_unique<Enemy>(200, 200, 200, 200)); //Ennemi dans la liste targets, en-dehors de la range

    enemies.push_back(std::make_unique<Enemy>(500, 500, 200, 200)); //Ennemi hors de la liste targets, en-dehors de la range
    enemies.push_back(std::make_unique<Enemy>(10, 10, 200, 200)); //Ennemi hors de la liste targets, dans la range

    tower->aim(enemies);

    EXPECT_EQ(tower->getTargets().size(), 1);
    EXPECT_EQ(enemies[1].get(), tower->getTargets()[0]);
}
