#include "Game.hpp"
#include <iostream>

using namespace std;
using namespace sf;

Gameplay::Gameplay() {
    // Création de la fenêtre
    window.create(VideoMode({ 1280u, 720u }), "KingTalk - Gameplay");

    // Chargement du monde
    unsigned tilesX = 1280 / 16;  // 80 tuiles
    unsigned tilesY = 720 / 16;   // 45 tuiles

    if (!world.load("assets/World/MapFarmers.tmx", tilesX, tilesY)) {
        cerr << "Erreur : impossible de charger le monde !" << endl;
    }

     Chargement du joueur
    if (!player.load("assets/characters/player.png"))
        //cerr << "Erreur: impossible de charger le joueur." << endl;

    // --- Musique ---
    if (!audio.loadMusic("assets/Audio/LilNasX.ogg")) { //passer de m4a à ogg
        cerr << "Erreur : impossible de charger la musique d'ambiance !" << endl;
    }
    else {
        audio.setVolume(70.f);
        audio.playMusic(true); // true = boucle infinie
    }
    
}

void Gameplay::run() {
    bool running = true;

    while (window.isOpen() && running) {
        while (auto eventOpt = window.pollEvent()) {
            const auto& event = *eventOpt;

            if (event.is<sf::Event::Closed>())
                window.close();
        }

        // Mise à jour du joueur
        float dt = clock.restart().asSeconds();
        player.handleInput();
        player.update(dt);

        // Affichage
        window.clear(Color::Black);
        world.render(window);
        player.render(window);
        window.display();
    }
}

