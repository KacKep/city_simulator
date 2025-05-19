#include "LiqourShop.hpp"

LiqourShop::LiqourShop()
	: Building("LiqourShop", LiqourShopTile) {

	setPosition({ 0,0 });
	setSize(sf::Vector2f{ (float)(rand() % 3 + 2) * 10,(float)(rand() % 3 + 2) * 10 });
	setFillColor(sf::Color::Yellow);
	setOutlineColor(sf::Color::Black);
	setOutlineThickness(1);
	setPrice((rand() % 10 + 1) * (-100));
	setProductValue((rand() % 8 + 3) * 10);
}