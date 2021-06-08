#include "Play_state.h"
#include <iostream>


Play_state::Play_state(std::string filePath) : Game_state()
{
    //current_game_state = make_unique<Play_state>("resources/NouvelleMapTest.tmx");
    
    tmx::Map map;
    map.load("resources/map1.tmx");
    layerZero = std::make_unique<MapLayer>(map, 0);
    layerOne = std::make_unique<MapLayer>(map, 1);
    mapSize.x = map.getTileCount().x;
    mapSize.y = map.getTileCount().y;
    blockSize = map.getTileSize().x;
    std::cout << mapSize.x << "\n";
    std::cout << mapSize.y << "\n";

    for (int i = 0; i < mapSize.x; i++)
    {
        for (int j = 0; j < mapSize.y; j++)
        {
            if (layerOne->getTile(i, j).ID == 4)
            {
                spawnBlock.x = i;
                spawnBlock.y = j;
            }
        }
    }
    std::cout << spawnBlock.x << "\n";
    std::cout << spawnBlock.y << "\n";
    //On peut récupérer l'id d'une tile, et en récupérant les coordonnées de chaque entitées on pourra déterminer sur quel block elles sont


    //F f;
    Enemy e(spawnBlock.x * blockSize + 16, spawnBlock.y * blockSize + 16, 20, 20);

    enemies = std::make_unique< std::vector<Enemy>>();
    enemies->push_back(e);

    Tower t(100.0, 100.0, Strategy::SingleTargetStrategy);

    towers = std::make_unique<std::vector<Tower>>();
    towers->push_back(t);
    //std::pair<F, Enemy> myPair(f, e);
    //enemy_map = std::make_unique<std::vector<std::pair<F, Enemy>>>();

    //enemy_map->push_back(myPair);



    //current_game_state = new Play_state("resources/Terrain-Test.tmx");
}


void Play_state::init()
{

}

void Play_state::update()
{
    if (!isLost && !isWon)
    {
        for (auto e = enemies->begin(); e != enemies->end(); e++)
        {


            switch (layerOne->getTile((e->getCoordinates().x + (e->getSize().x / 2)) / blockSize, (e->getCoordinates().y + (e->getSize().y / 2)) / blockSize).ID)
            {
            case 3:
                if (e->getState() != States::MOVING)
                {
                    e->triggerMachine(Triggers::A);

                }
                e->setMovement(MoveDirection::UP);
                break;
            case 4:
                if (e->getState() != States::MOVING)
                {
                    e->triggerMachine(Triggers::A);

                }
                e->setMovement(MoveDirection::UP);
                break;
            case 5:
                e->triggerMachine(Triggers::B);
                isLost = true;
                std::cout << "uLOST\n";
                break;

            case 7:
                e->setMovement(MoveDirection::RIGHT);
                break;
            case 8:
                e->setMovement(MoveDirection::LEFT);
                break;
            default:

                break;
            }


            e->update();
            std::cout << "x : " << enemies->at(0).getCoordinates().x << "\n";
            std::cout << "y : " << enemies->at(0).getCoordinates().y << "\n";
        }


    }
}

void Play_state::render(sf::RenderWindow& window)
{
    window.draw(*layerZero);
    for (int i = 0; i < enemies->size(); i++)
    {
        enemies->at(i).render(window);
    }
   //enemies->at(0).render(window);
    std::cout << enemies->at(0).getCoordinates().x << "test render\n";
    // render stuff here
}

