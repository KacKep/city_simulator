#include "Shop.hpp"

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

//Shop::~Shop()
//{
//}





//int Shop::giveValue() const {
//	return foodValue;
//}





//void Shop::draw(sf::RenderTarget& target, sf::RenderStates states) const
//{
//	target.draw(shape, states);
//}