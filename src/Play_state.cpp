#include "Play_state.h"
#include <iostream>
#include <pugixml.hpp>

using namespace std::chrono_literals;

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

    pugi::xml_document doc;

    pugi::xml_parse_result result = doc.load_file("resources/param.xml");

    nbEnemies = doc.child("Param").attribute("nbEnemies").as_int();
    deltaEnemies = doc.child("Param").attribute("deltaEnemies").as_int();
    buildTowerResource = doc.child("Param").attribute("buildTowerResource").as_int();

<<<<<<< HEAD
    time_since_last_spawn = std::chrono::high_resolution_clock::now();
=======
    std::cout <<"value  :"<< buildTowerResource << "\n";
>>>>>>> a6cb8dff7b0d67defb097bb2c7b87bf72d66c144

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

    wantsToBuild = false;
    buildResources = 12;

    sf::RectangleShape tmp(*(new sf::Vector2f(32,32)));
    //tmp.setPosition(200, 300);
    possibleBuild = tmp;
    buildType = TowerType::SingleTarget;

    
}


void Play_state::init()
{
    
}

void Play_state::update(std::chrono::time_point<std::chrono::high_resolution_clock> time_start)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        wantsToBuild = true;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            bool canBuildHere = true;
            for (int i = 0; i < towers.size(); i++)
            {
                
                if (towers[i]->getCoordinates() == possibleBuild.getPosition())
                {
                    canBuildHere = false;
                }
            }
            float x = possibleBuild.getPosition().x - (int)possibleBuild.getPosition().x % 32;
           
            float y = possibleBuild.getPosition().y - (int)possibleBuild.getPosition().y % 32;

            x = (int)(x / 32);
            x = (x > 15) ? 15 : x;
            y = (int)(y / 32);
            y = (y > 15) ? 15 : y;
            std::cout <<"x :"<< x<<"\n";
            std::cout << "y :" << y << "\n";

            //
            if (canBuildHere && layerOne->getTile(x, y).ID != 3 && layerOne->getTile(x, y).ID != 4 && layerOne->getTile(x, y).ID != 5 && layerOne->getTile(x, y).ID != 7 && layerOne->getTile(x, y).ID != 8)
            {
                buildTower();
            }
            //std::cout << "trying to build";
        }
    }
    else
    {
        wantsToBuild = false;
    }

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

            if (time_since_last_spawn <= time_start)
            {
                auto e = std::make_unique<Enemy>(spawnBlock.x * blockSize + 16, spawnBlock.y * blockSize + 16, 20, 20);
                enemies.push_back(std::move(e));
                time_since_last_spawn = time_start + std::chrono::seconds(2);
            }

            
            
            
        }
        for (int i = 1; i < towers.size(); i++)
        {
            towers[i]->update(enemies);
        }
        

        std::cout<<" size :" << enemies.size() << "\n";
    }
}

void Play_state::render(sf::RenderWindow& window)
{
    window.draw(*layerZero);

    //if(towers.size()>1)
    for (int i = 1; i < towers.size(); i++)
    {
        towers[i]->render(window);

    }

    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->render(window);
    }

    if (wantsToBuild)
    {
        float x = (sf::Mouse::getPosition(window).x) - (sf::Mouse::getPosition(window).x)%32;
        x = (x > 32 * 15) ? 32 * 15 : x;
        float y = sf::Mouse::getPosition(window).y -sf::Mouse::getPosition(window).y%32;
        y = (y > 32 * 15) ? 32 * 15 : y;
        possibleBuild.setPosition(*(new sf::Vector2f(x,y)));
        window.draw(possibleBuild);
        
    }

    


   //enemies->at(0).render(window);
    //std::cout << enemies[i].getCoordinates().x << "test render\n";
    // render stuff here
}

void Play_state::switchWantsToBuild()
{
    wantsToBuild = true;
}

void Play_state::buildTower()
{
    if (buildResources >= buildTowerResource)
    {
        towers.push_back(towers[0]->clone(possibleBuild.getPosition().x, possibleBuild.getPosition().y));
        buildResources -= buildTowerResource;
    }
    
}

