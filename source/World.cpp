#include "World.hpp"
#include <iostream>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

using namespace std;
using namespace sf;

World::World() {}

bool World::load(const string& texturePath, unsigned widthInTiles, unsigned heightInTiles) {
    // Charger le tilesheet
    vector<string> tilesetFiles = {
     "assets/environments/tilemap_packed.png",
     "assets/environments/Female Cow Brown.png",
     "assets/environments/Road copiar.png",
     "assets/environments/Chicken Red.png"
    };

    m_tilesets.clear(); // vide avant de recharger
    m_tilesets.resize(tilesetFiles.size());

    for (size_t i = 0; i < tilesetFiles.size(); ++i) {
        if (!m_tilesets[i].loadFromFile(tilesetFiles[i])) {
            cout << "Erreur chargement tileset : " << tilesetFiles[i] << endl;
            return false;
        }
    }

    
    // Créer les sprites de tuiles
    for (unsigned y = 0; y < heightInTiles; ++y) {
        for (unsigned x = 0; x < widthInTiles; ++x) {
            Sprite sprite(tileset);

            // Ici, on choisit toujours la tuile en haut à gauche du tilesheet pour l'instant
            sprite.setTextureRect(IntRect(0, 0, tileSize, tileSize));

            sprite.setPosition(static_cast<float>(x * tileSize),
                static_cast<float>(y * tileSize));

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
