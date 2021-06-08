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

enum class TowerType { SingleTarget, TwoTargets};

class Play_state : public Game_state
{
public:
	 void render(sf::RenderWindow& window) override;
	 void update(std::chrono::time_point<std::chrono::high_resolution_clock> time_start) override;
	 void init() override;
	Play_state();
	Play_state(std::string filePath); // On ouvre le fichier tmx donné par filePath et on en sort les informations du niveau
	void switchWantsToBuild();
	void buildTower();
	



private:
	std::unique_ptr<tmx::TileLayer> visual_layer;
	//DefenseMachine defense_layer[NB_TILES_VERTICAL * NB_TILES_HORIZONTAL] à créer en tant que vector
	//Path_tile path_layer[NB_TILES_VERTICAL * NB_TILES_HORIZONTAL] à créer en tant que vector

	
	//sf::RenderWindow window(sf::VideoMode(640, 640), "SFML window");
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

	//std::unique_ptr<std::vector<std::pair<F, Enemy>>> enemy_map;
	//std::unique_ptr<std::vector<Enemy>> enemies;
	//std::unique_ptr<std::vector<Tower>> towers;
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::vector<std::unique_ptr<Tower>> towers;

	bool wantsToBuild;
	int buildResources;

	sf::RectangleShape possibleBuild;


	TowerType buildType;

	std::chrono::time_point<std::chrono::high_resolution_clock> time_since_last_spawn;


};