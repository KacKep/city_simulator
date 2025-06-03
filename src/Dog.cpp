#include "Dog.hpp"
sf::Texture Dog::texture(std::string(RESOURCE_DIR) + "/Dog.png");
/*@File Dog is companion of Human. It will die if left alone for too long.
*/
Dog::Dog(Human* owner)
	:Animal(owner),
	followPosition(getOwner()->getPosition())
{

	setTexture(&texture);
	
	setAttack(10);
	setName("Dog");
}

void Dog::behavior() {
	//dog always follows owner if it is possible
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
			//if the hunger is 0, the animal starts to take damage
			addHealth(-2);
			addHappiness(-2);
		}
		else
		{
			//if the animal isnt staving, the hunger decreases as well as happiness
			addHunger(-10);
			addHappiness(-1);
		}

		/*std::cout <<"Hunger:" << getHunger() << std::endl;
		std::cout << "Health:" << getHealth() << std::endl;
		std::cout << "Money:" << getMoney() << std::endl;*/
		setTargetTile(GrassTile);
		//hunt();
		chooseTarget();
	}

	if (getBoundry().x < 10 || getBoundry().y < 10)
	{
		walkBasic();
		return;
	}
	
	if (checkBoundry(1, left) == false || checkBoundry(1, right) == false || checkBoundry(1, down) == false || checkBoundry(1, up) == false)
	{
		walkBasic();
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