#include "Play_state.h"
#include <iostream>
#include <pugixml.hpp>


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

    pugi::xml_parse_result result = doc.load_file("param.xml");

    nbEnemies = atoi(doc.child("Param").attribute("nbEnemies").value());
    deltaEnemies = atoi(doc.child("Param").attribute("deltaEnemies").value());
    nbEnemiesForTower = atoi(doc.child("Param").attribute("nbEnemiesForTower").value());

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
    buildResources = 10;

    sf::RectangleShape tmp(*(new sf::Vector2f(32,32)));
    //tmp.setPosition(200, 300);
    possibleBuild = tmp;
    buildType = TowerType::SingleTarget;

    
}


void Play_state::init()
{

}

void Play_state::update()
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
            if (canBuildHere)
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

            


            
            
            
        }
        for (int i = 1; i < towers.size(); i++)
        {
            towers[i]->update(enemies);
        }
        


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
        float y = sf::Mouse::getPosition(window).y -sf::Mouse::getPosition(window).y%32;
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
    if (buildResources >= 5)
    {
        towers.push_back(towers[0]->clone(possibleBuild.getPosition().x, possibleBuild.getPosition().y));
        buildResources -= 5;
    }
    
}

