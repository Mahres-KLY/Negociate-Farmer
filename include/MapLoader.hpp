#pragma once
#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace sf;

class MapLoader : public Drawable {
private:
    vector<Texture> m_tilesets;
    VertexArray m_vertices;

public:
    bool load(const string& tmxFile, const string& tilesetPath);
    void draw(RenderTarget& target, RenderStates states) const override;
};
