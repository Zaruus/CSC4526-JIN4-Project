#pragma once

#include "Game_state.h"

#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>




class Play_state : public Game_state
{
	 void render() override;
	 void init() override;
	Play_state();
	Play_state(std::string filePath); // On ouvre le fichier tmx donné par filePath et on en sort les informations du niveau


private:
	tmx::TileLayer * visual_layer;
	//DefenseMachine defense_layer[NB_TILES_VERTICAL * NB_TILES_HORIZONTAL] à créer en tant que vector
	//Path_tile path_layer[NB_TILES_VERTICAL * NB_TILES_HORIZONTAL] à créer en tant que vector

};