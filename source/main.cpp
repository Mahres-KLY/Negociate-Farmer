#include "Start.hpp"
#include "Gameplay.hpp"
#include <iostream>

int main() {
    RenderWindow window(VideoMode({ 800, 600 }), "Map Test");

    bool startGame = false;
    Start startMenu;
    startMenu.run(startGame);

    if (startGame) {
        Gameplay gameplay;
        gameplay.run();
    }

    return 0;
}
