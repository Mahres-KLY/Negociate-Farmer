#include "Gameplay.hpp"
#include <iostream>
using namespace std;
using namespace sf;

Gameplay::Gameplay(RenderWindow* window) : m_window(window) {
    m_player = Player();

    m_npcs.emplace_back(Vector2f(400, 400), "Voyageur", true);
    m_npcs.emplace_back(Vector2f(200, 300), "Fermier1");
    m_npcs.emplace_back(Vector2f(600, 300), "Fermier2");
    m_npcs.emplace_back(Vector2f(300, 200), "Fermiere1");
    m_npcs.emplace_back(Vector2f(500, 200), "Fermier3");
    m_npcs.emplace_back(Vector2f(700, 400), "Maitre de Ferme ");
    m_npcs.emplace_back(Vector2f(100, 400), "Maitresse de Ferme ");

    m_font.loadFromFile("assets/fonts/arial.ttf");
    m_text.setFont(m_font);
    m_text.setCharacterSize(20);
    m_text.setFillColor(Color::White);
    m_text.setString("");
}

void Gameplay::run() {
    Clock clock;
    while (m_window->isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        handleInput();
        m_player.update(deltaTime);
        update();
        render();
    }
}

void Gameplay::handleInput() {
    Event event;
    while (m_window->pollEvent(event)) {
        if (event.type == Event::Closed)
            m_window->close();
    }
}

void Gameplay::update() {
    bool nearNPC = false;

    for (auto& npc : m_npcs) {
        if (m_player.getBounds().intersects(npc.shape.getGlobalBounds())) {
            nearNPC = true;

            if (npc.isMainNPC)
                m_text.setString("Appuie sur E pour parler à " + npc.name);
            else
                m_text.setString("Appuie sur E pour jouer avec " + npc.name);

            if (Keyboard::isKeyPressed(Keyboard::E)) {
                if (npc.isMainNPC) {
                    inDialogue = true;
                    m_text.setString(npc.name + ": \"Bienvenue, jeune voyageur.\"");
                }
                else {
                    inMiniGame = true;
                    m_text.setString("Mini-jeu lancé avec " + npc.name + " !");
                }
            }
            break;
        }
    }

    if (!nearNPC && !inDialogue && !inMiniGame)
        m_text.setString("");
}

void Gameplay::render() {
    m_window->clear(Color(40, 40, 40));

    for (auto& npc : m_npcs)
        m_window->draw(npc.shape);

    m_player.draw(*m_window);
    m_window->draw(m_text);

    m_window->display();
}
