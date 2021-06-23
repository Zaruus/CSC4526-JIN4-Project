#pragma once

#include "Game_state.h"

#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "SFMLOrthogonalLayer.h"
#include "Enemy.h"
#include "Tower.h"
#include "SFML/Graphics/Text.hpp";

//enum class TowerType { SingleTarget, TwoTargets};

class Play_state : public Game_state
{
public:
	 void render(sf::RenderWindow& window) override;
	 void update(std::chrono::time_point<std::chrono::high_resolution_clock> time_start) override;
	 void init() override;
	Play_state();
	Play_state(std::string filePath, sf::RenderWindow& window); // On ouvre le fichier tmx donné par filePath et on en sort les informations du niveau
	void switchWantsToBuild();
	void buildTower();
	



private:
	std::unique_ptr<tmx::TileLayer> visual_layer;
	//DefenseMachine defense_layer[NB_TILES_VERTICAL * NB_TILES_HORIZONTAL] à créer en tant que vector
	//Path_tile path_layer[NB_TILES_VERTICAL * NB_TILES_HORIZONTAL] à créer en tant que vector

	
	
	std::unique_ptr<MapLayer> layerZero;
	std::unique_ptr<MapLayer> layerOne;

	sf::Vector2f mapSize;
	sf::Vector2f spawnBlock;

	bool isWon = false;
	bool isLost = false;

	int blockSize;

	int nbEnemies;
	int deltaEnemies;
	int buildTowerResource;
	int HalfLifeKnockIndex;

	
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::vector<std::unique_ptr<Tower>> towers;
	std::vector<std::unique_ptr<sf::Vector2f>> spawnBlocks;
	int currentSpawnId;

	bool wantsToBuild;
	int buildResources;


	//variables pour la construction de towers
	sf::RectangleShape possibleBuild;
	Strategy buildStrategy;
	int qPressedCounter;
	int dPressedCounter;

	//temps entre chaque spawn d'ennemi
	std::chrono::time_point<std::chrono::high_resolution_clock> time_since_last_spawn;


	std::vector<std::unique_ptr<float>> doorsLife;

	int spawnIndex;

	

	
	


};