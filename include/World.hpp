#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using namespace std;
using namespace sf;

class World {
private:
    Texture tileset;
    vector<Sprite> tiles;
    unsigned tileSize = 16;   // adapté à Tiny Town
public:
    World();
    bool load(const string& texturePath, unsigned widthInTiles, unsigned heightInTiles);
    void render(RenderWindow& window);
};