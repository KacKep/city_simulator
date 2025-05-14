#include "Human2.hpp"

Human2::Human2()
	:Entity()
{
	setID();
	std::cout << "\nID:" << getID();
	setFillColor(sf::Color::Yellow);
	if (getID()>0)
	{
		chooseTarget();
		setPosition(getTarget());
	}
	
	
	
	setHealth(100);
	setHunger(100);
	setAttack(5);
}
Human2::~Human2(){
}

void Human2::walk() {
	chooseTarget();
	
	if (getTarget().x < getPosition().x)//Left
	{
    setPosition(sf::Vector2f(getPosition().x - 10.f, getPosition().y));

	}
	else if (getTarget().x > getPosition().x)//Right
	{
		setPosition(sf::Vector2f(getPosition().x + 10.f, getPosition().y));
	}
	else if (getTarget().y < getPosition().y)//Down
	{
		setPosition(sf::Vector2f(getPosition().x, getPosition().y - 10.f));
	}
	else if (getTarget().y > getPosition().y) //Up
	{
		setPosition(sf::Vector2f(getPosition().x, getPosition().y + 10.f));
	}

	return;
}

void Human2::chooseTarget() {

	if (getTarget()==getPosition())
	{
		BuildingList place;
		if (getHunger() < 50)
		{
			place = ShopTile;
		}
		else
		{
			place = PavementTile;
		}
		for (size_t i = 0; i < 3; i++)
		{


			//setTarget(sf::Vector2f({ rand() % getBoundry().x, rand() % getBoundry().y }));
			int xMap = rand() % getBoundry().x;
			int yMap = rand() % getBoundry().y;
			int X2;
			int Y2;
			for (int y = 0; y < getBoundry().y ; y++)
			{
				for (int x = 0; x < getBoundry().x ; x++)
				{
					X2 = (xMap + x) % (getBoundry().x);
					Y2 = (yMap + y) % (getBoundry().y);
					if (getMap()[X2][Y2] == place) {
						//std::cout << "\n Targetx" << TargetPosition.x << " ,Targety" << TargetPosition.y;
						setTarget( sf::Vector2f(Y2 * 10, X2 * 10));
						//setTarget();
						return;
					}
				}

			}
			if (i == 0)
			{
				place = PavementTile;
			}
			else
			{
				switch (rand() % 2)
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
	if (getTarget()==getPosition() /*|| ++unstuck == (getBoundry().x * getBoundry().y) / 4*/) {
		setPosition( getTarget());
		//unstuck = 0;
		setHunger(getHunger() - 10);
		//setTarget(false);
	}
}