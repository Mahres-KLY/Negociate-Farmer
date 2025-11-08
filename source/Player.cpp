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
    if (Keyboard::isKeyPressed(Keyboard::Key::W)) movement.y -= 1.f;
    if (Keyboard::isKeyPressed(Keyboard::Key::S)) movement.y += 1.f;
    if (Keyboard::isKeyPressed(Keyboard::Key::A)) movement.x -= 1.f;
    if (Keyboard::isKeyPressed(Keyboard::Key::D)) movement.x += 1.f;

    if (sprite)
        sprite->move(movement * speed * 0.016f); // petit déplacement fixe pour test
}

void Player::update(float dt) {
    // Ici tu pourras gérer les collisions ou animations plus tard
}

void Player::render(RenderWindow& window) {
    if (sprite)
        window.draw(*sprite);
}
