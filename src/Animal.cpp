#include "Animal.hpp"

Animal::Animal(Human* human)
	:Entity(),
	owner(human), //that's the only way, said the yt guy about agregations (he was talking about using refrence in the constructor)
	followPosition(human->getPosition())
{
	
	setID();
	std::cout << "\nID:" << getID();
	
		setTarget(owner->getTarget());
		setPosition(getTarget());

	if (!texture.loadFromFile(std::string(RESOURCE_DIR) + "/snake.png")) {
		setFillColor(sf::Color::Cyan);
		std::cout << "no animal texture" << std::endl;
	}
	else {
		setTexture(&texture);
		
	}
	setOutlineColor(sf::Color::Black);
	setOutlineThickness(1);
	//sf::Color(rand() % 256, rand() % 256, rand() % 256, 255)
	setType(animal);
	
}


Animal::~Animal() {
	owner = nullptr;
}



//walking
void Animal::walk() {
	if (isDead())
	{
		//std::cout <<"\tx:" << getPosition().x << " \ty:" << getPosition().y << std::endl;
		return;
	}
	

	if (getHealth() <= 0) {
		std::cout << "animal nr " << getID() << " died" << std::endl;
		setDead(true);
		setFillColor(sf::Color::Transparent);
		setOutlineThickness(0);
	}
	behavior();

	//setFillColor(sf::Color(getFillColor().r % 256, getFillColor().g % 256, getFillColor().b, 255));


	return;
}

void Animal::behavior() {
	if (owner && !owner->isDead())
	{
		if (abs(owner->getPosition().y-getPosition().y)<5.f&& abs(owner->getPosition().x - getPosition().x) < 5.f)
		{
			followPosition = owner->getPosition();
			return;
		}
		
		setPosition(followPosition);
		followPosition = owner->getPosition();
		return;
	}
	if (getTarget() == getPosition())
	{
		if (getHunger()<= 0)
			{
				setHunger(0);
				setHealth( - 2);
			}
			else
			{
				setHunger(-10);
			}

		/*std::cout <<"Hunger:" << getHunger() << std::endl;
		std::cout << "Health:" << getHealth() << std::endl;
		std::cout << "Money:" << getMoney() << std::endl;*/
		setTargetTile(PavementTile);
		chooseTarget();
	}
		


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
	//if (getTarget()==getPosition() /*|| ++unstuck == (getBoundry().x * getBoundry().y) / 4*/) {
	//	setPosition( getTarget());
	//	//unstuck = 0;
	//	
	//	//setTarget(false);
	//}
}

void Animal::fight(Entity* enemy) {
	if (owner)
	{
		if (enemy->getID() == owner->getID())
		{
			std::cout << "pat pat" << std::endl;
			if (owner->getMoney()>=100 && getHealth()<=50)
			{
				owner->setMoney(-100);
				setHealth(100 - getHealth());
			}
			return;
		}
	}

	if (enemy->getType() == human && rand()%10==0)
	{
		std::cout << "dog got addopted by" << owner->getID()<<std::endl;
		Human* master = dynamic_cast<Human*>(enemy);
        owner = master;
		owner->setMoney(-100);
		setHealth(100 - getHealth());
		setHunger(100 - getHunger());
	}
	
	for (;;) {

		enemy->setHealth(-getAttack());
		if (enemy->getHealth() <= 0) {

			break;
		}

		setHealth(-enemy->getAttack());
		if (getHealth() <= 0) {

			break;
		}

		// there is <=  becaus item will add to zero so there is no problem with swiftness 9999 
		if (rand() % 10 <= 0) {
			enemy->walk();
			break;
		}

		if (rand() % 10 <= 0) {
			walk();
			break;
		}
	}
}