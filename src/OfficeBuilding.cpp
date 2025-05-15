#include "OfficeBuilding.hpp"

OfficeBuilding::OfficeBuilding()
	: Building("OfficeBuilding", OfficeBuildingTile) {

	setPosition({ 10,10 });
	setSize(sf::Vector2f{ 40,80 });
	setFillColor(sf::Color::Black);
	setMoney(0);
	

	setPrice((rand() % 5 + 1) * 10);
	setProductValue((rand() % 10 + 1) * 100);
}
OfficeBuilding::~OfficeBuilding()
{
}