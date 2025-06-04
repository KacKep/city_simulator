#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
/// <summary>
/// File from sfml tutorial on sfml website allows for optimised background
/// </summary>
class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    bool load(const std::filesystem::path& tileset, const int* tiles, unsigned int width, unsigned int height);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


    sf::Vector2u tileSize;
    sf::VertexArray m_vertices;
    sf::Texture     m_tileset;
};
