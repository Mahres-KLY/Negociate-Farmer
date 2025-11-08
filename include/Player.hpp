#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Player {
private:
    Texture texture;
    unique_ptr<Sprite> sprite;
    float speed = 200.f;

public:
    Player();
    bool load(const string& path);
    void handleInput();
    void update(float dt);
    void render(sf::RenderWindow& window);
};
