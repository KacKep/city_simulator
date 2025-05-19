#include "Hospital.hpp"

Hospital::Hospital()
	: Building("Hospital", HospitalTile) {

	setPosition({ 50,30 });
	setSize(sf::Vector2f{(float)(rand() % 4 + 2) * 10,(float)(rand() % 4 + 2) * 10 });
	setFillColor(sf::Color::Red);
	setOutlineColor(sf::Color::Black);
	setOutlineThickness(1);
	setPrice((rand() % 10 + 5) * (-100));
	setProductValue((rand() % 5 + 1) * 10);
}
