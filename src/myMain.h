#pragma once

#include <tmxlite/Map.hpp>

struct game_state {
    // this contains the state of your game, such as positions and velocities
};

int myMain();
bool handle_events();
void update(game_state*);
void render(game_state const&);
game_state interpolate(game_state const& current, game_state const& previous, float alpha);