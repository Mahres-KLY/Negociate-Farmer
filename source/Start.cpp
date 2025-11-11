#include "Start.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

Start::Start() {
    // Création de la fenêtre
    window.create(VideoMode(Vector2u(WINDOW_W, WINDOW_H)), "Territory Farm - Menu");

    // Chargement du fond
    if (!backgroundTexture.loadFromFile("assets/environments/Cover Start.png")) {
        cerr << "Impossible de charger l'image de fond !" << endl;
        exit(1);
    }

    // On attache la texture APRÈS l'avoir chargée
    backgroundSprite = make_unique<Sprite>(backgroundTexture);
    backgroundSprite->setScale(Vector2f(static_cast<float>(WINDOW_W) / backgroundTexture.getSize().x,
        static_cast<float>(WINDOW_H) / backgroundTexture.getSize().y));

    // Police
    if (!font.openFromFile("assets/fonts/arial.ttf")) {
        cerr << "Impossible de charger la police !" << endl;
        exit(1);
    }

    // Bouton PLAY
    playButton.setSize({ 200.f, 60.f });
    playButton.setPosition({
        (static_cast<float>(WINDOW_W) - 200.f) / 2.f,
        (static_cast<float>(WINDOW_H) - 60.f) / 2.f
        });
    playButton.setFillColor(Color::White);

    // Texte
    playText = make_unique<Text>("PLAY", font, 32);
    playText->setFillColor(Color::Black);
    auto bounds = playText->getLocalBounds();
    playText->setPosition({
        playButton.getPosition().x + (playButton.getSize().x - bounds.size.x) / 2.f,
        playButton.getPosition().y + (playButton.getSize().y - bounds.size.y) / 2.f
        });
}

void Start::run(bool& startGame) {
    while (window.isOpen() && !startGame) {
        while (auto eventOpt = window.pollEvent()) {
            const auto& event = *eventOpt;

            if (event.is<Event::Closed>()) {
                window.close();
            }
            else if (event.is<Event::MouseButtonPressed>()) {
                auto mouseEvent = event.getIf<Event::MouseButtonPressed>();
                if (mouseEvent->button == Mouse::Button::Left) {
                    Vector2f mousePos = window.mapPixelToCoords(mouseEvent->position);
                    if (playButton.getGlobalBounds().contains(mousePos)) {
                        startGame = true;
                        window.close();
                    }
                }
            }
        }

        window.clear();
        window.draw(*backgroundSprite);
        window.draw(playButton);
        window.draw(*playText);
        window.display();
    }
}
