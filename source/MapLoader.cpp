#include "MapLoader.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;
using namespace tmx;


bool MapLoader::load(const string& tmxFile, const string& tilesetPath)
{
    Map map;
    if (!map.load("assets/World/MapFarmers.tmx")) {
        cout << "Erreur chargement de la map: " << endl;
        return false;
    }

    const auto& layers = map.getLayers();
    if (layers.empty()) return false;

    // On prend le premier calque (terrain)
    const auto* layer = dynamic_cast<const TileLayer*>(layers[0].get());
    if (!layer) return false;




    //Chargement de tout mes tilesets dans ma Map
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



    const auto tileSize = map.getTileSize();
    const auto mapSize = map.getTileCount();

    m_vertices.setPrimitiveType(Quads);
    m_vertices.resize(mapSize.x * mapSize.y * 4);

    const auto& tiles = layer->getTiles();
    for (unsigned y = 0; y < mapSize.y; ++y) {
        for (unsigned x = 0; x < mapSize.x; ++x) {
            unsigned tileNumber = tiles[y * mapSize.x + x].ID;
            if (tileNumber == 0) continue;

            tileNumber -= 1;
            int tu = tileNumber % (m_tilesets[0].getSize().x / tileSize.x);
            int tv = tileNumber / (m_tilesets[0].getSize().x / tileSize.x);

            Vertex* quad = &m_vertices[(x + y * mapSize.x) * 4];
            quad[0].position = Vector2f(x * tileSize.x, y * tileSize.y);
            quad[1].position = Vector2f((x + 1) * tileSize.x, y * tileSize.y);
            quad[2].position = Vector2f((x + 1) * tileSize.x, (y + 1) * tileSize.y);
            quad[3].position = Vector2f(x * tileSize.x, (y + 1) * tileSize.y);

            quad[0].texCoords = Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
    }

    return true;
}

void MapLoader::draw(RenderTarget& target, RenderStates states) const
{
    states.texture = &m_tilesets[0];
    target.draw(m_vertices, states);
}
