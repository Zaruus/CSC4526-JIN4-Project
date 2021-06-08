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


  
    auto e = std::make_unique<Enemy>(spawnBlock.x * blockSize + 16, spawnBlock.y * blockSize + 16, 20, 20);

    enemies.push_back(std::move(e));

    

    auto t = std::make_unique<Tower>(200,200, Strategy::SingleTargetStrategy);

   
    towers.push_back(std::move(t));
    
}


void Play_state::init()
{

}

void Play_state::update()
{
    if (!isLost && !isWon)
    {
        for (int i = 0;i<enemies.size();i++)
        {

            if (enemies[i]->getState() == States::Dead)
            {
                enemies.erase(enemies.begin() + i);
            }
            else
            {
                switch (layerOne->getTile((enemies[i]->getCoordinates().x + (enemies[i]->getSize().x / 2)) / blockSize, (enemies[i]->getCoordinates().y + (enemies[i]->getSize().y / 2)) / blockSize).ID)
                {
                case 3:
                    if (enemies[i]->getState() != States::MOVING)
                    {
                        enemies[i]->triggerMachine(Triggers::A);

                    }
                    enemies[i]->setMovement(MoveDirection::UP);
                    break;
                case 4:
                    if (enemies[i]->getState() != States::MOVING)
                    {
                        enemies[i]->triggerMachine(Triggers::A);

                    }
                    enemies[i]->setMovement(MoveDirection::UP);
                    break;
                case 5:
                    enemies[i]->triggerMachine(Triggers::B);
                    isLost = true;
                    std::cout << "uLOST\n";
                    break;

                case 7:
                    enemies[i]->setMovement(MoveDirection::RIGHT);
                    break;
                case 8:
                    enemies[i]->setMovement(MoveDirection::LEFT);
                    break;
                default:

                    break;
                }


                enemies[i]->update();
            }

            


            
            towers[i]->update(enemies);
            
        }


    }
}

void Play_state::render(sf::RenderWindow& window)
{
    window.draw(*layerZero);

    for (int i = 0; i < towers.size(); i++)
    {
        towers[i]->render(window);

    }

    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->render(window);
    }

    


   //enemies->at(0).render(window);
    //std::cout << enemies[i].getCoordinates().x << "test render\n";
    // render stuff here
}

