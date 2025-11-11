#include "Start.hpp"
#include "Gameplay.hpp"
#include <iostream>

using namespace sf;

int main() {
    bool startGame = false;

    // Étape 1 : Menu de démarrage
    Start startMenu;
    startMenu.run(startGame);

    // Étape 2 : Si le joueur a cliqué sur PLAY, on lance le jeu
    if (startGame) {
        // Création de la fenêtre de jeu (réutilisation des dimensions du menu)
        RenderWindow gameWindow(VideoMode({ 1280, 720 }), "Territory Farm - Gameplay");

        // Lancement du gameplay avec la fenêtre
        Gameplay gameplay(&gameWindow);
        gameplay.run();
    }

    return 0;
}
