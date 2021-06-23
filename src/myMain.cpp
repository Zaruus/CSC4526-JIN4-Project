#include "myMain.h"



using namespace std;

using namespace std::chrono_literals;

// we use a fixed timestep of 1 / (60 fps) = 16 milliseconds
constexpr std::chrono::nanoseconds timestep(16ms);


std::unique_ptr<Game_state> current_game_state;             
std::unique_ptr<sf::RenderWindow> window;


bool handle_events() {
    // poll for events

    return false; // true if the user wants to quit the game
}

void init()
{
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(16*32, 16*32), "Evil Science");
    
    current_game_state = std::make_unique<Play_state>("resources/map1.tmx",*window);
    
}

void update(game_state*, std::chrono::time_point<std::chrono::high_resolution_clock> time_start) {

    current_game_state->update(time_start);
   

}

void render(game_state const&) {
    current_game_state->render(*window);

    
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
            if (event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window->setView(sf::View(visibleArea));
            }
        }
        

        auto delta_time = clock::now() - time_start;
        time_start = clock::now();
        lag += std::chrono::duration_cast<std::chrono::nanoseconds>(delta_time);

        quit_game = handle_events();

        // update game logic as lag permits
        while (lag >= timestep) {
            lag -= timestep;

            previous_state = current_state;
            update(&current_state, clock::now()); // update at a fixed rate each time
        }

        // calculate how close or far we are from the next timestep
        auto alpha = (float)lag.count() / timestep.count();
        auto interpolated_state = interpolate(current_state, previous_state, alpha);


        window->clear(sf::Color::Black);

        
        

        

        
        render(interpolated_state);
      

        window->display();

       

        
       


    }

    

    return 0;
}