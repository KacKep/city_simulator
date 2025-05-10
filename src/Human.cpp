#include "Human.hpp"
#include <iostream>
Human::Human(sf::Vector2f a) {
	boundry = a;
	Position = sf::Vector2f(rand() % ((int)boundry.x) * 10, (rand() % (int)boundry.y) * 10 );
	shape.setSize( sf::Vector2f(10, 10));
	shape.setFillColor(sf::Color::Red);
	xVelocity = 10;
	yVelocity = 10;
	isTarget = false;
	TargetPosition = Position;
	unstuck = 0;
	std::cout << a.x <<"\n"<<a.y;
}
//float tolerance = 5.0f;

Human::~Human() {

}



void Human::setTarget(bool a) {
	this->isTarget = a;
}

bool Human::ActiveTarget() {
	return isTarget;
}

sf::Vector2f Human::getPosition() {
	return Position;
}

void Human::Target(const std::vector<std::vector<int>>& Intmap) {

	if (!ActiveTarget())
	{
		TargetPosition = sf::Vector2f((rand() % ((int)boundry.y)) * 10, (rand() % ((int)boundry.x)) * 10);
		xMap = TargetPosition.x / 10;
		yMap = TargetPosition.y / 10;
		for (int y = 0; y < boundry.y && !ActiveTarget(); y++)
		{
			for (int x = 0; x < boundry.x && !ActiveTarget(); x++)
			{
				X2 = (xMap + x) % ((int)boundry.x);
				Y2 = (yMap + y) % ((int)boundry.y);
				if (Intmap[Y2][X2] < 3) {

					TargetPosition = sf::Vector2f( X2 * 10,Y2 * 10);
					setTarget(true);
					break;
				}
			}

		}
		
	}
	if ((abs(TargetPosition.x - Position.x) < 9.0f &&
		abs(TargetPosition.y - Position.y) < 9.0f) || ++unstuck==boundry.x+boundry.y) {
		Position = TargetPosition;
		unstuck = 0;
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
	


bool Human::checkBoundry() {
	if (Position.x < 0 || Position.x>boundry.x - 10)
	{
		return false;
	}
	if (Position.y < 0 || Position.y>boundry.y - 10)
	{
		return false;
	}
	return true;
}

void Human::walk(const std::vector<std::vector<int>>& Intmap) {
	
	xMap = Position.x / 10;
	yMap = Position.y / 10;
	
	if (checkBoundry()) {
		// Move in X direction
		if (TargetPosition.x < Position.x  && Intmap[yMap][xMap - 1] < 3) {
			Position.x -= xVelocity;
		}
		else if (TargetPosition.x > Position.x && Intmap[yMap][xMap + 1] < 3) {
			Position.x += xVelocity;
		}
		// Move in Y direction
		else if (TargetPosition.y < Position.y && Intmap[yMap - 1][xMap] < 3) {
			Position.y -= yVelocity;
		}
		else if (TargetPosition.y > Position.y &&  Intmap[yMap + 1][xMap] < 3) {
			Position.y += yVelocity;
		}
	}
	else if (TargetPosition.x < Position.x)
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
	else if (TargetPosition.y > Position.y) {
		Position.y += yVelocity;
	}

	/*Position.x += xVelocity;
	Position.y += yVelocity;*/
	//shape.move(Move);

	//checkBoundry();
	shape.setPosition(Position);

	std::cout <<"X" << Position.x << " ,Y " << Position.y<<"\n";

	Target(Intmap);
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
