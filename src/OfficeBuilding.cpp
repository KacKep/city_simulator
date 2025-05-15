#include "OfficeBuilding.hpp"

OfficeBuilding::OfficeBuilding()
	: Building("OfficeBuilding", OfficeBuildingTile) {

	setPosition({ 10,10 });
	setSize(sf::Vector2f{ 40,80 });
	setFillColor(sf::Color::Black);
	setMoney(0);
	//price = (rand() % 10 + 1) * 10;
	//foodValue = (rand() % 5 + 1) * 10;

	setPrice((rand() % 10 +1) * 10);
	setProductValue((rand() % 5 + 1) * 10);
}
OfficeBuilding::~OfficeBuilding()
{
}