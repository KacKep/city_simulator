#include "Cat.hpp"
#include "Dog.hpp"
#include "Entity.hpp"

Cat::Cat(Human* owner)
	:Dog(owner)
{
	if (!texture.loadFromFile(std::string(RESOURCE_DIR) + "/Cat.png")) {
		setFillColor(sf::Color::Magenta);
		std::cout << "no animal texture" << std::endl;
	}
	else {
		setTexture(&texture);

	}
}

void Cat::behavior() {
	if (getTarget() == getPosition())
	{
		if (getHunger() <= 0)
		{
			addHunger(0);
			addHealth(-2);
		}
		else
		{
			addHunger(-5);
		}
		if (getHealth()>100)
		{
			addHealth(100 - getHealth());
		}

		/*std::cout <<"Hunger:" << getHunger() << std::endl;
		std::cout << "Health:" << getHealth() << std::endl;
		std::cout << "Money:" << getMoney() << std::endl;*/
		if (rand()%2==0)
		{
			setTargetTile(FlowersTile);

		}
		else {
			setTargetTile(GrassTile);
		}
		// his is the 'hunt' method for animals. It will be added later to animal rn it's sprint to deliver the class hierarchy.
		hunt();

		
		chooseTarget();
	}

	basicWalk();
}