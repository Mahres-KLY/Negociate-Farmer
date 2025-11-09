#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using namespace sf;
using namespace std;

class NPC {
public:
    RectangleShape shape;
    string name;
    bool isMainNPC;

    NPC(Vector2f pos, string name, bool isMain = false) {
        this->name = name;
        this->isMainNPC = isMain;
        shape.setSize({40, 60});
        shape.setFillColor(isMain ? Color::Green : Color::Yellow);
        shape.setPosition(pos);
    }
};

class Player {
public:
    RectangleShape shape;

    Player(Vector2f pos = {400, 500}) {
        shape.setSize({40, 60});
        shape.setFillColor(Color::Cyan);
        shape.setPosition(pos);
    }

    void move(Vector2f dir) { shape.move(dir); }

    FloatRect getBounds() const { return shape.getGlobalBounds(); }
};

class Gameplay {
private:
    RenderWindow* m_window;
    Player m_player;
    vector<NPC> m_npcs;
    Font m_font;
    Text m_text;
    bool inMiniGame = false;
    bool inDialogue = false;

public:
    Gameplay(RenderWindow* window);
    void run();
    void handleInput();
    void update();
    void render();
};
