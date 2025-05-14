#include "Human.hpp"


Human::Human(sf::Vector2f a) {
	boundry = a;
	Position = sf::Vector2f((rand() % (int)boundry.y) * 10,rand() % ((int)boundry.x) * 10  );
	shape.setSize( sf::Vector2f(10, 10));
	shape.setFillColor(sf::Color::Black);
	xVelocity = 10;
	yVelocity = 10;
	isTarget = false;
	TargetPosition = Position;
	unstuck = 0;
	hunger = 100;

	//std::cout << a.x <<"\n"<<a.y;
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
		BuildingList place;
		if (hunger<50)
		{
			place = ShopTile;
		}
		else
		{
			place = PavementTile;
		}
		for (size_t i = 0; i < 3; i++)
		{


			TargetPosition = sf::Vector2f((rand() % ((int)boundry.x)), (rand() % ((int)boundry.y)));
			xMap = TargetPosition.x;
			yMap = TargetPosition.y;
			for (int y = 0; y < boundry.y && !ActiveTarget(); y++)
			{
				for (int x = 0; x < boundry.x && !ActiveTarget(); x++)
				{
					X2 = (xMap + x) % ((int)boundry.x);
					Y2 = (yMap + y) % ((int)boundry.y);
					if (Intmap[X2][Y2] == place) {
						//std::cout << "\n Targetx" << TargetPosition.x << " ,Targety" << TargetPosition.y;
						TargetPosition = sf::Vector2f(Y2 * 10, X2 * 10);
						setTarget(true);
						return;
					}
				}

			}
			if (i==0)
			{
				place = PavementTile;
			}
			else
			{
				switch (rand()%2)
				{
				case 0:
					place = GrassTile;
					break;
				default:
					place = FlowersTile;
					break;
				}
			}
			
		}
		
	}
	if ((abs((float)TargetPosition.x - (float)Position.x) <= 9.0f &&
		abs((float)TargetPosition.y - (float)Position.y) <= 9.0f) || ++unstuck==(boundry.x*boundry.y)/4) {
		Position = TargetPosition;
		unstuck = 0;
		hunger -= 10;
		setTarget(false);
	}
}
	
void Human::BasicWalk() {
	if (TargetPosition.x < Position.x)
	{
		Position.x += -10.f;
		std::cout << "go left";

	}
	else if (TargetPosition.x > Position.x) {
		Position.x += 10.f;
	}
	else if (TargetPosition.y < Position.y)
	{
		Position.y += -10.f;
	}
	else if (TargetPosition.y > Position.y) {
		Position.y += 10.f;
	}
}

bool Human::checkBoundry(unsigned int a,int check) {
	
	switch (check) {
	case 1: // Left
		//std::cout << check << "- left\n";
		return (int)Position.x/10 > a + 1;
	case 2: // Right
		//std::cout << check << "- right\n";
		return (int)Position.x/10 < boundry.x - a - 1;
	case 3: // Up
		//std::cout << check << "- up\n";
		return (int)Position.y/10 > a + 1;
	case 4: // Down
		//std::cout << check << "- down\n";
		return (int)Position.y/10 < boundry.y - a - 1;
	default:
		return false;
	}
}

void Human::walk(const std::vector<std::vector<int>>& Intmap) {
	Target(Intmap);
	xMap = Position.x / 10;
	yMap = Position.y / 10;
	//std::cout << "\nXmap" << xMap << " ,Ymap " << yMap ;

	/*if (checkBoundry(1,1)&& TargetPosition.x < Position.x)
	{
		Position.x -= xVelocity;
	} 
	else if(checkBoundry(1, 2)&& (TargetPosition.x > Position.x))
	{
		Position.x += xVelocity;
	}
	else if(checkBoundry(1,3)&& TargetPosition.y < Position.y)
	{
		Position.y -= yVelocity;
	}
	else if (checkBoundry(1, 4)&& (TargetPosition.y > Position.y))
	{
		Position.y += yVelocity;
	}
	else
	{*/
		BasicWalk();
	//}

	

	Target(Intmap);
	shape.setPosition(Position);

	//std::cout <<"\nX" << Position.x << " ,Y " << Position.y<<"\n";

	
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
