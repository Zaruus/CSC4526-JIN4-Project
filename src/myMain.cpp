#include "myMain.h"



using namespace std;

using namespace std::chrono_literals;

// we use a fixed timestep of 1 / (60 fps) = 16 milliseconds
constexpr std::chrono::nanoseconds timestep(16ms);


std::unique_ptr<Game_state> current_game_state;
std::unique_ptr<sf::RenderWindow> window;
//sf::RenderWindow window(sf::VideoMode(640, 640), "SFML window");
std::unique_ptr<MapLayer> layerZero;
std::unique_ptr<MapLayer> layerOne;

sf::Vector2f mapSize;
sf::Vector2f spawnBlock;

bool isWon = false;
bool isLost = false;

int blockSize;



//std::unique_ptr<std::vector<std::pair<F, Enemy>>> enemy_map;
std::unique_ptr<std::vector<Enemy>> enemies;

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
    map.load("resources/map1.tmx");
    layerZero = make_unique<MapLayer>(map, 0);
    layerOne = make_unique<MapLayer>(map, 1);
    mapSize.x = map.getTileCount().x;
    mapSize.y = map.getTileCount().y;
    blockSize = map.getTileSize().x;
    std::cout << mapSize.x << "\n";
    std::cout << mapSize.y << "\n";
    
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
    

    //F f;
    Enemy e(spawnBlock.x*blockSize +16,spawnBlock.y*blockSize +16,20,20);

    enemies = std::make_unique< std::vector<Enemy>>();
    enemies->push_back(e);
    //std::pair<F, Enemy> myPair(f, e);
    //enemy_map = std::make_unique<std::vector<std::pair<F, Enemy>>>();

    //enemy_map->push_back(myPair);



    //current_game_state = new Play_state("resources/Terrain-Test.tmx");
}

void update(game_state*) {

    /*for (int i = 0; i < enemies->size(); i++)
    {
        std::cout << "x : " << enemies->at(i).getCoordinates().x << "\n";
        std::cout << "y : " << enemies->at(i).getCoordinates().y << "\n";
    }*/
    if (!isLost && !isWon)
    {
        for (auto e = enemies->begin(); e != enemies->end(); e++)
        {


            switch (layerOne->getTile((e->getCoordinates().x + (e->getSize().x / 2)) / blockSize, (e->getCoordinates().y + (e->getSize().y / 2)) / blockSize).ID)
            {
            case 3:
                if (e->getState() != States::MOVING)
                {
                    e->triggerMachine(Triggers::A);

                }
                e->setMovement(MoveDirection::UP);
                break;
            case 4:
                if (e->getState() != States::MOVING)
                {
                    e->triggerMachine(Triggers::A);

                }
                e->setMovement(MoveDirection::UP);
                break;
            case 5:
                e->triggerMachine(Triggers::B);
                isLost = true;
                std::cout << "uLOST\n";
                break;

            case 7:
                e->setMovement(MoveDirection::RIGHT);
                break;
            case 8:
                e->setMovement(MoveDirection::LEFT);
                break;
            default:

                break;
            }


            e->update();
            std::cout << "x : " << enemies->at(0).getCoordinates().x << "\n";
            std::cout << "y : " << enemies->at(0).getCoordinates().y << "\n";
    }

    
    }







    // update game logic here

   

}

void render(game_state const&) {
    

    for (int i = 0; i < enemies->size(); i++)
    {
        enemies->at(i).render(*window);
    }
    enemies->at(0).render(*window);
    std::cout << enemies->at(0).getCoordinates().x << "test render\n";
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

        
        

        

        window->draw(*layerZero);
        render(interpolated_state);
        //window->clear(sf::Color::White);

        window->display();

        if (isLost)
        {
           
            //window->
            quit_game = true;
        }


    }

    

    return 0;
}