#include "MapLoader.hpp"

bool MapLoader::load(const string& tmxFile, const string& tilesetPath) {
    tmx::Map map;
    if (!map.load(tmxFile)) {
        return false;
    }

    const auto& layers = map.getLayers();
    if (layers.empty()) return false;

    const tmx::TileLayer* layer = dynamic_cast<const tmx::TileLayer*>(layers[0].get());
    if (!layer) return false;

    if (!m_tilesets[0].loadFromFile(tilesetPath)) {
        return false;
    }

    const auto tileSize = map.getTileSize();
    const auto mapSize = map.getTileCount();

    m_vertices.setPrimitiveType(PrimitiveType::Quads);
    m_vertices.resize(mapSize.x * mapSize.y * 4);

    const auto& tiles = layer->getTiles();
    for (unsigned y = 0; y < mapSize.y; ++y) {
        for (unsigned x = 0; x < mapSize.x; ++x) {
            unsigned tileNumber = tiles[y * mapSize.x + x].ID;
            if (tileNumber == 0) continue;

            tileNumber -= 1;
            int tu = static_cast<int>(tileNumber % (m_tilesets[0].getSize().x / tileSize.x));
            int tv = static_cast<int>(tileNumber / (m_tilesets[0].getSize().x / tileSize.x));

            Vertex* quad = &m_vertices[(x + y * mapSize.x) * 4];

            quad[0].position = Vector2f(static_cast<float>(x * tileSize.x), static_cast<float>(y * tileSize.y));
            quad[1].position = Vector2f(static_cast<float>((x + 1) * tileSize.x), static_cast<float>(y * tileSize.y));
            quad[2].position = Vector2f(static_cast<float>((x + 1) * tileSize.x), static_cast<float>((y + 1) * tileSize.y));
            quad[3].position = Vector2f(static_cast<float>(x * tileSize.x), static_cast<float>((y + 1) * tileSize.y));

            quad[0].texCoords = Vector2f(static_cast<float>(tu * tileSize.x), static_cast<float>(tv * tileSize.y));
            quad[1].texCoords = Vector2f(static_cast<float>((tu + 1) * tileSize.x), static_cast<float>(tv * tileSize.y));
            quad[2].texCoords = Vector2f(static_cast<float>((tu + 1) * tileSize.x), static_cast<float>((tv + 1) * tileSize.y));
            quad[3].texCoords = Vector2f(static_cast<float>(tu * tileSize.x), static_cast<float>((tv + 1) * tileSize.y));
        }
    }

    return true;
}

void MapLoader::draw(RenderTarget& target, RenderStates states) const {
    states.texture = &m_tilesets[0];
    target.draw(m_vertices, states);
}
