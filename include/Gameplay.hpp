#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Player.hpp"

using namespace sf;
using namespace std;

struct NPC {
    RectangleShape shape;
    string name;
    bool isMainNPC = false;

    NPC(Vector2f pos, string name, bool main = false) {
        shape.setSize({ 40, 60 });
        shape.setPosition(pos);
        shape.setFillColor(main ? Color::Yellow : Color::Cyan);
        this->name = name;
        isMainNPC = main;
    }
};

class Gameplay {
private:
    RenderWindow* m_window;
    Player m_player;
    vector<NPC> m_npcs;
    Font m_font;
    Text m_text;
    bool inDialogue = false;
    bool inMiniGame = false;

public:
    Gameplay(RenderWindow* window);
    void run();
    void handleInput();
    void update();
    void render();
};
