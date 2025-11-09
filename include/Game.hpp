#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "World.hpp"
#include "Audio.hpp"

using namespace std;
using namespace sf;

class Gameplay {
private:
    RenderWindow window;
    Player player;
    World world;
    Audio audio;
    Clock clock; // Pour gérer le deltaTime

public:
    Gameplay();
    void run();
};
