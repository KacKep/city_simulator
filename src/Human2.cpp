#include "Human2.hpp"

Human2::Human2()
	:Entity()
{
	setFillColor(sf::Color::Yellow);
	float a = rand() % getBoundry().x * 10;
	float b = rand() % getBoundry().x * 10;
	setPosition(sf::Vector2f(a,b));
	setHealth(100);
	setHunger(100);
	setAttack(5);
}
Human2::~Human2(){
}

void Human2::walk() {
	return;
}

void Human2::chooseTarget() {
	return;
}