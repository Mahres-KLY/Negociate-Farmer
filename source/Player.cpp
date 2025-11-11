#include "Player.hpp"

Player::Player() {
    if (!texture.loadFromFile("assets/player.png")) {
        cout << "Erreur chargement texture du joueur !" << endl;
    }
    sprite = Sprite(texture);
    sprite.setPosition(Vector2f(400, 300));
    speed = 200.f;
}

void Player::handleInput(float deltaTime) {
    Vector2f movement(0.f, 0.f);

    if (Keyboard::isKeyPressed(Keyboard::Key::Z)) movement.y -= speed * deltaTime;
    if (Keyboard::isKeyPressed(Keyboard::Key::S)) movement.y += speed * deltaTime;
    if (Keyboard::isKeyPressed(Keyboard::Key::Q)) movement.x -= speed * deltaTime;
    if (Keyboard::isKeyPressed(Keyboard::Key::D)) movement.x += speed * deltaTime;

    sprite.move(movement);
}

void Player::update(float deltaTime) {
    handleInput(deltaTime);
}

void Player::draw(RenderWindow& window) {
    window.draw(sprite);
}

void Player::move(Vector2f dir) {
    sprite.move(dir);
}

Vector2f Player::getPosition() const {
    return sprite.getPosition();
}

FloatRect Player::getBounds() const {
    return sprite.getGlobalBounds();
}
