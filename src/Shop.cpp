#include "Shop.hpp"

Shop::Shop ()
	: Building("Shop", ShopTile){
	
	setPosition({ 0,0 });
	setSize( sf::Vector2f{10,10});
	setFillColor(sf::Color::Blue);
	setMoney(0);
	price = (rand() % 10 + 1) * 10;
	foodValue = (rand() % 5 + 1) * 10;

	setProductValue(foodValue);
}
Shop::~Shop()
{
}





//int Shop::giveValue() const {
//	return foodValue;
//}





//void Shop::draw(sf::RenderTarget& target, sf::RenderStates states) const
//{
//	target.draw(shape, states);
//}