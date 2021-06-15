#include "Play_state.h"
#include <iostream>
#include <pugixml.hpp>


using namespace std::chrono_literals;

Play_state::Play_state(std::string filePath) : Game_state()
{
    //current_game_state = make_unique<Play_state>("resources/NouvelleMapTest.tmx");
    
    tmx::Map map;
    map.load("resources/map2.tmx");
    layerZero = std::make_unique<MapLayer>(map, 0);
    layerOne = std::make_unique<MapLayer>(map, 1);
    mapSize.x = map.getTileCount().x;
    mapSize.y = map.getTileCount().y;
    blockSize = map.getTileSize().x;
    

    //On parse le document xml pour r�cup�rer les donn�es du niveaux
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("resources/param.xml");
    nbEnemies = doc.child("Param").attribute("nbEnemies").as_int();
    deltaEnemies = doc.child("Param").attribute("deltaEnemies").as_int();
    buildTowerResource = doc.child("Param").attribute("buildTowerResource").as_int();


    time_since_last_spawn = std::chrono::high_resolution_clock::now();

    

    //ON r�cup�re les coordonn�es du block o� les ennemis devront spawn
    for (int i = 0; i < mapSize.x; i++)
    {
        for (int j = 0; j < mapSize.y; j++)
        {
            if (layerOne->getTile(i, j).ID == 4)
            {
                spawnBlocks.push_back(std::make_unique<sf::Vector2f>(i, j));
                //spawnBlock.x = i;
                //spawnBlock.y = j;
            }
        }
    }
    currentSpawnId = 0;
    
    


  //On cr�e l'ennemi prototype qui clonera les autres
    auto e = std::make_unique<Enemy>(spawnBlocks[0]->x * blockSize * (3 / 2), spawnBlocks[0]->y * blockSize * (3 / 2), 20, 20);

    enemies.push_back(std::move(e));

    
    //On cr�e la tour prototype qui clonera les autres
    auto t = std::make_unique<Tower>(200,200, Strategy::SingleTargetStrategy);

   
    towers.push_back(std::move(t));

    //On initialise les variables de constructions de tower
    wantsToBuild = false;
    buildResources = 12;

    sf::RectangleShape tmp(*(new sf::Vector2f(32,32)));
    
    possibleBuild = tmp;
    buildType = TowerType::SingleTarget;
    
    

    
}


void Play_state::init()
{
    
}

void Play_state::update(std::chrono::time_point<std::chrono::high_resolution_clock> time_start)
{
    //On observe pour contruire une tower
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
            float x = possibleBuild.getPosition().x - (int)possibleBuild.getPosition().x % blockSize;
           
            float y = possibleBuild.getPosition().y - (int)possibleBuild.getPosition().y % blockSize;

            x = (int)(x / blockSize);
            
            x = (x > (mapSize.x - 1)) ? (mapSize.x - 1) : x;
            y = (int)(y / blockSize);
            y = (y > (mapSize.y - 1)) ? (mapSize.y - 1) : y;
            

            //
            if (canBuildHere && layerOne->getTile(x, y).ID != 3 && layerOne->getTile(x, y).ID != 4 && layerOne->getTile(x, y).ID != 5 && layerOne->getTile(x, y).ID != 7 && layerOne->getTile(x, y).ID != 8)
            {
                buildTower();
            }
           
        }
    }
    else
    {
        wantsToBuild = false;
    }

    //on update les ennemis 

    if (!isLost && !isWon)
    {
        for (int i = 1;i<enemies.size();i++)
        {

            if (enemies[i]->getState() == States::Dead)
            {
                enemies.erase(enemies.begin() + i);
                buildResources+=3;
            }
            else
            {
                


                // On utilise des coordonn�es permettant � l'ennemi de rester sur le chemin visuellement
                int ex;
                int ey;

                switch (enemies[i]->getMoveDirection())
                {
                case MoveDirection::UP:
                    ex = (enemies[i]->getCoordinates().x) / blockSize;
                    ey = (enemies[i]->getCoordinates().y+16) / blockSize;

                    break;
                case MoveDirection::DOWN:
                    ex = (enemies[i]->getCoordinates().x) / blockSize;
                    ey = (enemies[i]->getCoordinates().y - 16) / blockSize;
                    break;
                case MoveDirection::RIGHT:
                    ex = (enemies[i]->getCoordinates().x-16) / blockSize;
                    ey = (enemies[i]->getCoordinates().y) / blockSize;
                    break;
                case MoveDirection::LEFT:
                    ex = (enemies[i]->getCoordinates().x + 16) / blockSize;
                    ey = (enemies[i]->getCoordinates().y) / blockSize;
                    break;

                default:
                    ex = (enemies[i]->getCoordinates().x) / blockSize;
                    ey = (enemies[i]->getCoordinates().y) / blockSize;
                    break;
                }

                //switch (layerOne->getTile((enemies[i]->getCoordinates().x + (enemies[i]->getSize().x / 2)) / blockSize, (enemies[i]->getCoordinates().y + (enemies[i]->getSize().y / 2)) / blockSize).ID)
                switch (layerOne->getTile(ex,ey).ID)
                {
                case 3:
                    if (enemies[i]->getState() != States::MOVING)
                    {
                        enemies[i]->triggerMachine(Triggers::InitialToMoving);

                    }
                    enemies[i]->setMovement(MoveDirection::UP);
                    break;
                case 4:
                    if (enemies[i]->getState() != States::MOVING)
                    {
                        enemies[i]->triggerMachine(Triggers::InitialToMoving);

                    }
                    enemies[i]->setMovement(MoveDirection::UP);
                    break;
                case 5:
                    enemies[i]->triggerMachine(Triggers::MovingToFinal);
                    isLost = true;
                    std::cout << "The game is lost\n";
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
        //On update les towers
        for (int i = 1; i < towers.size(); i++)
        {
            towers[i]->update(enemies);
        }
        if (time_since_last_spawn <= time_start && nbEnemies > 0)
        {
            
            //enemies.push_back(enemies[0]->clone(spawnBlock.x * blockSize + 16, spawnBlock.y * blockSize + 16));
            enemies.push_back(enemies[0]->clone(spawnBlocks[currentSpawnId]->x * blockSize + 16, spawnBlocks[currentSpawnId]->y * blockSize + 16));
            currentSpawnId = (currentSpawnId + 1) % spawnBlocks.size();


            time_since_last_spawn = time_start + std::chrono::seconds(deltaEnemies);
            nbEnemies--;
            
        }
        

        
    }
}

void Play_state::render(sf::RenderWindow& window)
{
    window.draw(*layerZero);

    
    for (int i = 1; i < towers.size(); i++)
    {
        towers[i]->render(window);

    }

    for (int i = 1; i < enemies.size(); i++)
    {
        enemies[i]->render(window);
    }

    if (wantsToBuild)
    {
        //On build obligatoirement sur une tile
        float x = (sf::Mouse::getPosition(window).x) - (sf::Mouse::getPosition(window).x)% blockSize;
        x = (x > blockSize * (mapSize.x-1)) ? blockSize * (mapSize.x - 1) : x;
        float y = sf::Mouse::getPosition(window).y -sf::Mouse::getPosition(window).y% blockSize;
        y = (y > blockSize * (mapSize.y - 1)) ? blockSize * (mapSize.y - 1) : y;
        possibleBuild.setPosition(*(new sf::Vector2f(x,y)));
        window.draw(possibleBuild);
        
    }

    
}

void Play_state::switchWantsToBuild()
{
    wantsToBuild = true;
}

void Play_state::buildTower()
{
    //Construit une tower
    if (buildResources >= buildTowerResource)
    {
        towers.push_back(towers[0]->clone(possibleBuild.getPosition().x, possibleBuild.getPosition().y));
        buildResources -= buildTowerResource;
    }
    
}

