#pragma once

#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

sf::Texture giveTexture(std::string path);
void background(sf::RenderWindow& window, int seed);