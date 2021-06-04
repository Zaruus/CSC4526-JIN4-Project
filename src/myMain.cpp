#include "myMain.h"
#include <chrono>
#include <pugixml.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

#include <iostream>

#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "Game_state.h"
#include "Play_state.h"

#include "SFMLOrthogonalLayer.h"


using namespace std;

using namespace std::chrono_literals;

// we use a fixed timestep of 1 / (60 fps) = 16 milliseconds
constexpr std::chrono::nanoseconds timestep(16ms);


std::unique_ptr<Game_state> current_game_state;
std::unique_ptr<sf::RenderWindow> window;
std::unique_ptr<MapLayer> layerZero;

//Game_state* current_game_state;

bool handle_events() {
    // poll for events

    return false; // true if the user wants to quit the game
}

void init()
{
    // Initialize your data here
    current_game_state = make_unique<Play_state>("resources/Terrain-Test.tmx");
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(640, 640), "SFML window");
    tmx::Map map;
    map.load("resources/montest.tmx");
    layerZero = make_unique<MapLayer>(map, 0);

    
    
    //current_game_state = new Play_state("resources/Terrain-Test.tmx");
}

void update(game_state*) {
    // update game logic here

    /*
    tmx::Map map;
    if (map.load("resources/Terrain-Test.tmx"))
    {
        const auto& layers = map.getLayers();
        for (const auto& layer : layers)
        {
            if (layer->getType() == tmx::Layer::Type::Object)
            {
                const auto& objectLayer = layer->getLayerAs<tmx::ObjectGroup>();
                const auto& objects = objectLayer.getObjects();
                for (const auto& object : objects)
                {
                    //do stuff with object properties
                }
            }
            else if (layer->getType() == tmx::Layer::Type::Tile)
            {
                const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
                //read out tile layer properties etc...
            }
        }

        const auto& tilesets = map.getTilesets();
        for (const auto& tileset : tilesets)
        {
            //read out tile set properties, load textures etc...
        }
    }*/
    
}

void render(game_state const&) {
    // render stuff here
}

game_state interpolate(game_state const& current, game_state const& previous, float alpha) {
    game_state interpolated_state;

    // interpolate between previous and current by alpha here

    return interpolated_state;
}

int myMain() {
    using clock = std::chrono::high_resolution_clock;

    init();
    
    
    std::chrono::nanoseconds lag(0ns);
    auto time_start = clock::now();
    bool quit_game = false;

    game_state current_state;
    game_state previous_state;

    while (!quit_game)
   
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        auto delta_time = clock::now() - time_start;
        time_start = clock::now();
        lag += std::chrono::duration_cast<std::chrono::nanoseconds>(delta_time);

        quit_game = handle_events();

        // update game logic as lag permits
        while (lag >= timestep) {
            lag -= timestep;

            previous_state = current_state;
            update(&current_state); // update at a fixed rate each time
        }

        // calculate how close or far we are from the next timestep
        auto alpha = (float)lag.count() / timestep.count();
        auto interpolated_state = interpolate(current_state, previous_state, alpha);
        
        render(interpolated_state);

        window->clear(sf::Color::Black);
        
        window->draw(*layerZero);
        //window->clear(sf::Color::White);

        window->display();
    }

    return 0;
}