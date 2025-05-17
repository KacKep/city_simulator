#include "Hospital.hpp"

Hospital::Hospital()
	: Building("Hospital", HospitalTile) {

	setPosition({ 50,30 });
	setSize(sf::Vector2f{ 50,30 });
	setFillColor(sf::Color::Red);

	setPrice((rand() % 10 + 5) * (-100));
	setProductValue((rand() % 5 + 1) * 10);
}
