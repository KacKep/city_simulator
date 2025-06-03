#include "Polytechnic.hpp"
/** file Makes human smarter so they can earn more money*/

Polytechnic::Polytechnic()
    : Building("Polytechnic", PolytechnicTile) {

    setPosition({ 0,0 });
	setSize(sf::Vector2f{ 90, 90 });
    setFillColor(sf::Color(60, 60, 100));
    setOutlineColor(sf::Color::Black);
    setOutlineThickness(1);
    setPrice((rand() % 10 + 1) * (-200));
    setProductValue((rand() % 10 + 5) * 5);
}