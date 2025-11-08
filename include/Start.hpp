#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

using namespace sf;
using namespace std;

// Taille de la fenêtre
constexpr unsigned int WINDOW_W = 1280;
constexpr unsigned int WINDOW_H = 720;

class Start {
private:
    Texture backgroundTexture;
    unique_ptr<Sprite> backgroundSprite;

public:
    RenderWindow window;
    Font font;
    RectangleShape playButton;
    unique_ptr<Text> playText;

    Start();                  // Constructeur
    void run(bool& startGame); // Boucle principale du menu
};