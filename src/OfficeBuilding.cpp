#include "OfficeBuilding.hpp"
/**@File gives not permament jobs to humans
 *  the more semesters a human has graduated, the more money he earns
 */
OfficeBuilding::OfficeBuilding()
	: Building("OfficeBuilding", OfficeBuildingTile) {

	setPosition({ 10,10 });
	setSize(sf::Vector2f{ (float)(rand()%4+3)*10,(float)(rand() % 4 + 3) * 10 });
	setFillColor(sf::Color::Cyan);
	
	setOutlineColor(sf::Color::Black);
	setOutlineThickness(1);

	setProductValue(0);
	setPrice((rand() % 10 + 5) * 100);
}
