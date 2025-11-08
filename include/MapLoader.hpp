#pragma once
#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>

using namespace std;
using namespace sf;

class MapLoader : public Drawable {
private:
    VertexArray m_vertices;
    Texture m_tileset;

public:
    bool load(const string& tmxFile, const string& tilesetPath);
    virtual void draw(RenderTarget& target, RenderStates states) const override;
};