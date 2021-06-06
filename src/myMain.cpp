#include "myMain.h"



using namespace std;

using namespace std::chrono_literals;

// we use a fixed timestep of 1 / (60 fps) = 16 milliseconds
constexpr std::chrono::nanoseconds timestep(16ms);


std::unique_ptr<Game_state> current_game_state;
std::unique_ptr<sf::RenderWindow> window;
std::unique_ptr<MapLayer> layerZero;
std::unique_ptr<MapLayer> layerOne;



std::unique_ptr<std::vector<std::pair<F, Enemy>>> enemy_map;

//Game_state* current_game_state;

bool handle_events() {
    // poll for events

    return false; // true if the user wants to quit the game
}

void init()
{
    // Initialize your data here
    //current_game_state = make_unique<Play_state>("resources/NouvelleMapTest.tmx");
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(640, 640), "SFML window");
    tmx::Map map;
    map.load("resources/retest.tmx");
    layerZero = make_unique<MapLayer>(map, 0);
    layerOne = make_unique<MapLayer>(map, 1);

    //On peut récupérer l'id d'une tile, et en récupérant les coordonnées de chaque entitées on pourra déterminer sur quel block elles sont
    tmx::TileLayer::Tile testTile = layerOne->getTile(8, 0);
    std::cout << testTile.ID << "\n";

    F f;
    Enemy e(0, 0);
    std::pair<F, Enemy> myPair(f, e);
    enemy_map = std::make_unique<std::vector<std::pair<F, Enemy>>>();

    enemy_map->push_back(myPair);



    //current_game_state = new Play_state("resources/Terrain-Test.tmx");
}

void update(game_state*) {

    for (int i = 0; i < enemy_map->size(); i++)
    {
        std::cout << "x : " << enemy_map->at(i).second.getCoordinates().x << "\n";
        std::cout << "y : " << enemy_map->at(i).second.getCoordinates().y << "\n";
    }


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
    init();
    using clock = std::chrono::high_resolution_clock;




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