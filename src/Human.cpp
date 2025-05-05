#include "Human.hpp"

Human::Human(int seed) {
	seed = seed;
	Position = sf::Vector2f(100, 100);
	shape.setSize( sf::Vector2f(10, 10));
	shape.setFillColor(sf::Color::Red);
	xVelocity = 10;
	yVelocity = 10;
	isTarget = false;
	TargetPosition = Position;
}
//float tolerance = 5.0f;

Human::~Human() {

}

int Human::getSeed() {
	return seed;
}

void Human::setTarget(bool a) {
	this->isTarget = a;
}

bool Human::getTarget() {
	return isTarget;
}

sf::Vector2f Human::getPosition() {
	return Position;
}

void Human::Target() {

	if (!getTarget())
	{
		TargetPosition = sf::Vector2f((rand() % 118)*10, (rand() % 62)*10);
		setTarget(true);
	}
	if (abs(TargetPosition.x - Position.x) < 5.0f &&
		abs(TargetPosition.y - Position.y) < 5.0f) {
		Position = TargetPosition;
		setTarget(false);
	}
	//float dx = TargetPosition.x - Position.x;
	//float dy = TargetPosition.y - Position.y;
	//float distanceSquared = dx * dx + dy * dy;

	//if (distanceSquared < 100.0f) { // 100 = 10px tolerance (10^2)
	//	Position = TargetPosition; // snap to it
	//	setTarget(0);
	//}
}
	


void Human::checkBoundry() {
	if (Position.x < 0 || Position.x>1280 - 10)
	{
		xVelocity *= -1;
	}
	if (Position.y < 0 || Position.y>720 - 10)
	{
		yVelocity *= -1;
	}
}

void Human::walk() {
	
	
	if (TargetPosition.x < Position.x)
	{
		Position.x -= xVelocity;
	}
	else if (TargetPosition.x > Position.x) {
		Position.x += xVelocity;
	}
	else if (TargetPosition.y < Position.y)
	{
		Position.y -= yVelocity;
	}
	else /*if (TargetPosition.y > Position.y)*/ {
		Position.y += yVelocity;
	}

	/*Position.x += xVelocity;
	Position.y += yVelocity;*/
	//shape.move(Move);

	checkBoundry();
	shape.setPosition(Position);
	Target();
}

void Human::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	
	states.transform *= getTransform();
	target.draw(shape, states);
}

//void Human::draw(sf::RenderWindow& window) {
//	walk();
//
//	window.draw(shape);
//}
