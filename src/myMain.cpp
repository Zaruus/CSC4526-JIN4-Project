#include "myMain.h"



using namespace std;

using namespace std::chrono_literals;

// we use a fixed timestep of 1 / (60 fps) = 16 milliseconds
constexpr std::chrono::nanoseconds timestep(16ms);


std::unique_ptr<Game_state> current_game_state;
std::unique_ptr<sf::RenderWindow> window;
/*
//sf::RenderWindow window(sf::VideoMode(640, 640), "SFML window");
std::unique_ptr<MapLayer> layerZero;
std::unique_ptr<MapLayer> layerOne;

sf::Vector2f mapSize;
sf::Vector2f spawnBlock;

bool isWon = false;
bool isLost = false;

int blockSize;

//std::unique_ptr<std::vector<std::pair<F, Enemy>>> enemy_map;
std::unique_ptr<std::vector<Enemy>> enemies;*/

//Game_state* current_game_state;

bool handle_events() {
    // poll for events

    return false; // true if the user wants to quit the game
}

void init()
{
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(640, 640), "SFML window");
    current_game_state = std::make_unique<Play_state>("resources/map1.tmx");
    
}

void update(game_state*) {

    current_game_state->update();
    

   

}

void render(game_state const&) {
    current_game_state->render(*window);

    /*for (int i = 0; i < enemies->size(); i++)
    {
        enemies->at(i).render(*window);
    }
    enemies->at(0).render(*window);
    std::cout << enemies->at(0).getCoordinates().x << "test render\n";*/
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
            // "close requested" event: we close the window
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


        window->clear(sf::Color::Black);

        
        

        

        
        render(interpolated_state);
        //window->clear(sf::Color::White);

        window->display();

        /*if (isLost)
        {
            event.type = sf::Event::Closed;
            //window->
            quit_game = true;
        }*/

        
       


    }

    

    return 0;
}