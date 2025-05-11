#include "Shop.hpp"

Shop::Shop ()
	: Building("Shop", ShopTile)
{
	
	shape.setSize( sf::Vector2f{20,20});
	shape.setFillColor(sf::Color::Blue);
	money = 0;
	price = (rand() % 10 + 1) * 10;
	satiety = (rand() % 5 + 1) * 10;
}
Shop::~Shop()
{
}

//std::string& Shop::getName() {
//	return this->name;  // or customize however you'd like
//}

int Shop::getTile() const  {
	return BuildingList::ShopTile;
}

std::string& Shop::getName() {
	return this->name;
}

sf::Vector2f Shop::getPosition() {
	return this->Position;
}

sf::RectangleShape& Shop::getShape() {
	return shape;
}

void Shop::setPosition(sf::Vector2f position) {
	this->Position = position;
	this->shape.setPosition(position);
}


void Shop::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
}