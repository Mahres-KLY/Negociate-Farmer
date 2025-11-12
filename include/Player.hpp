#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class Player {
private:
    Sprite sprite;
    Texture texture;
    float speed;
    bool textureLoaded;

public:
    Player();
    void handleInput(float deltaTime);
    void update(float deltaTime);
    void draw(RenderWindow& window);
    void move(Vector2f dir);
    Vector2f getPosition() const;
    FloatRect getBounds() const;
};
