#include "Hospital.hpp"

Hospital::Hospital()
	: Building("Hospital", HospitalTile) {

	setPosition({ 50,30 });
	setSize(sf::Vector2f{ 50,30 });
	setFillColor(sf::Color::Red);
	setMoney(0);
	//price = (rand() % 10 + 1) * 10;
	//foodValue = (rand() % 5 + 1) * 10;

	setPrice((rand() % 10 + 5) * (-100));
	setProductValue((rand() % 5 + 1) * 10);
}
Hospital::~Hospital()
{
}