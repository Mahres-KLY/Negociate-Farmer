#include "World.hpp"
#include <iostream>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

using namespace std;
using namespace sf;

World::World() {}

bool World::load(const string& texturePath, unsigned widthInTiles, unsigned heightInTiles) {
    vector<string> tilesetFiles = {
        "assets/environments/tilemap_packed.png",
        "assets/environments/Female Cow Brown.png",
        "assets/environments/Road copiar.png",
        "assets/environments/Chicken Red.png"
    };

    m_tilesets.clear();
    m_tilesets.resize(tilesetFiles.size());

    for (size_t i = 0; i < tilesetFiles.size(); ++i) {
        if (!m_tilesets[i].loadFromFile(tilesetFiles[i])) {
            cout << "Erreur chargement tileset : " << tilesetFiles[i] << endl;
            return false;
        }
    }

    for (unsigned y = 0; y < heightInTiles; ++y) {
        for (unsigned x = 0; x < widthInTiles; ++x) {
            Sprite sprite(m_tilesets[0]);
            sprite.setTextureRect(IntRect(Vector2i(0, 0), Vector2i(tileSize, tileSize)));
            sprite.setPosition(Vector2f(static_cast<float>(x * tileSize),
                static_cast<float>(y * tileSize)));
            tiles.push_back(sprite);
        }
    }
    return true;
}

void World::render(RenderWindow& window) {
    for (auto& tile : tiles) {
        window.draw(tile);
    }
}
