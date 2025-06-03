#include "Shop.hpp"
/** file sells food to human
*/
Shop::Shop ()
	: Building("Shop", ShopTile){
	
	setPosition({ 0,0 });
	setSize( sf::Vector2f{ (float)(rand() % 4 + 2) * 10,(float)(rand() % 4 + 2) * 10 });
	setFillColor(sf::Color::Blue);
	setOutlineColor(sf::Color::Black);
	setOutlineThickness(1);
	setPrice((rand() % 10 + 1) * (-10));
	setProductValue((rand() % 8 + 3) * 10);
}
