#include "World.hpp"
#include <iostream>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

using namespace std;
using namespace sf;

World::World() {}

bool World::load(const string& texturePath, unsigned widthInTiles, unsigned heightInTiles) {
    // Charger le tilesheet
    if (!tileset.loadFromFile(texturePath)) {
        cerr << "Erreur : impossible de charger le tileset '" << texturePath << "'\n";
        return false;
    }

    tiles.clear();
    tiles.reserve(widthInTiles * heightInTiles);

    
    // Créer les sprites de tuiles
    for (unsigned y = 0; y < heightInTiles; ++y) {
        for (unsigned x = 0; x < widthInTiles; ++x) {
            sf::Sprite sprite(tileset);

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