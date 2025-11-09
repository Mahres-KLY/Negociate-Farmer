#include "Player.hpp"
#include <iostream>

using namespace std;
using namespace sf;

Player::Player() {}

bool Player::load(const string& path) {
    if (!texture.loadFromFile(path)) {
        cerr << "Erreur: texture joueur non trouvée." << endl;
        return false;
    }
    sprite = make_unique<Sprite>(texture);
    sprite->setPosition({ 640.f, 360.f });
    return true;
}

void Player::handleInput() {
    Vector2f movement(0.f, 0.f);
    if (Keyboard::isKeyPressed(Keyboard::Key::Z)) movement.y -= 1.f;
    if (Keyboard::isKeyPressed(Keyboard::Key::S)) movement.y += 1.f;
    if (Keyboard::isKeyPressed(Keyboard::Key::Q)) movement.x -= 1.f;
    if (Keyboard::isKeyPressed(Keyboard::Key::D)) movement.x += 1.f;

    if (sprite)
        sprite->move(movement * speed * 0.016f); // petit déplacement fixe
}

void Player::update(float dt) {
    // les collisions ou animations 
}

void Player::render(RenderWindow& window) {
    if (sprite)
        window.draw(*sprite);
}
