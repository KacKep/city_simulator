#include "Dog.hpp"
sf::Texture Dog::texture(std::string(RESOURCE_DIR) + "/Dog.png");

Dog::Dog(Human* owner)
	:Animal(owner),
	followPosition(getOwner()->getPosition())
{

	setTexture(&texture);
	
	setAttack(10);
	setName("Dog");
}

void Dog::behavior() {
	if (getOwner() && !getOwner()->isDead())
	{
		if (abs(getOwner()->getPosition().y - getPosition().y) < 9.f && abs(getOwner()->getPosition().x - getPosition().x) < 9.f)
		{
			
			return;
		}
		setPosition(followPosition);
		followPosition = getOwner()->getPosition();
		

		return;
	}
	else if (abs(getTarget().y - getPosition().y) < 51.f && abs(getTarget().x - getPosition().x)<51.f)
	{
		setTarget(getPosition());
		if (getHunger() <= 0)
		{
			addHunger(0);
			addHealth(-2);
		}
		else
		{
			addHunger(-10);
		}

		/*std::cout <<"Hunger:" << getHunger() << std::endl;
		std::cout << "Health:" << getHealth() << std::endl;
		std::cout << "Money:" << getMoney() << std::endl;*/
		setTargetTile(GrassTile);
		//hunt();
		chooseTarget();
	}

	
	if (checkBoundry(1, left) == false || checkBoundry(1, right) == false || checkBoundry(1, down) == false || checkBoundry(1, up) == false)
	{
		walkBasic();
		//the most important uselles return lol
		return;
	}
	else if (walkSpecific(PavementTile))
	{

	}
	else if (walkSpecific(RoadTile))
	{

	}
	else if (walkCircle(PavementTile))
	{

	}
	else
	{
		walkBasic();
	}


}