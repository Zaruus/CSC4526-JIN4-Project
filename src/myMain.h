#pragma once

#include <tmxlite/Map.hpp>
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

#pragma once

#include <tmxlite/Map.hpp>
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

#include "Enemy.h"
#include "fsm.h"

#include <iostream>

struct game_state {
    // this contains the state of your game, such as positions and velocities
};

int myMain();
bool handle_events();
void update(game_state*);
void render(game_state const&);
game_state interpolate(game_state const& current, game_state const& previous, float alpha);