#include "Shop.hpp"

Shop::Shop ()
	: Building("Shop", ShopTile){
	
	setPosition({ 0,0 });
	setSize( sf::Vector2f{20,20});
	setFillColor(sf::Color::Blue);

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