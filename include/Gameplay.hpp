#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "World.hpp"
#include "HUD.hpp"
#include "Audio.hpp"

using namespace std;
using namespace sf;

class Gameplay {
private:
    sf::RenderWindow window;
    Player player;
    World world;
    HUD hud;
    Audio audio;
    sf::Clock clock; // Pour gérer le deltaTime

public:
    Gameplay();
    void run();
};