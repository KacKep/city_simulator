#include "Dog.hpp"

Dog::Dog(Human* human)
	:Entity(),
	owner(human), //that's the only way, said the yt guy about agregations (he was talking about using refrence in the constructor)
	followPosition(human->getPosition()),
	name("Dog")
{
	setID();
		setTarget(owner->getTarget());
		setPosition(getTarget());

	if (!texture.loadFromFile(std::string(RESOURCE_DIR) + "/Dog.png")) {
		setFillColor(sf::Color::Black);
		std::cout << "no animal texture" << std::endl;
	}
	else {
		setTexture(&texture);
		
	}
	setType(animal);
	setAttack(10);
}

std::string Dog::getName() {
	return name;
}
void Dog::setName(std::string name) {
	this->name = name;
}

Dog::~Dog() {
	owner = nullptr;
}
Human* Dog::getOwner() const 
{ return owner; }


//walking
void Dog::walk() {
	if (isDead())
	{
		//std::cout <<"\tx:" << getPosition().x << " \ty:" << getPosition().y << std::endl;
		return;
	}
	

	if (getHealth() <= 0) {
		//std::cout << "animal nr " << getID() << " died" << std::endl;
		setDead(true);
		setFillColor(sf::Color::Transparent);
		setOutlineThickness(0);
	}
	behavior();

	//setFillColor(sf::Color(getFillColor().r % 256, getFillColor().g % 256, getFillColor().b, 255));


	return;
}

void Dog::behavior() {
	if (owner && !owner->isDead())
	{
		if (abs(owner->getPosition().y-getPosition().y)<3.f&& abs(owner->getPosition().x - getPosition().x) < 3.f)
		{
			followPosition = owner->getPosition();
			return;
		}
		/*if (abs(owner->getPosition().y - getPosition().y) > 11.f && abs(owner->getPosition().x - getPosition().x) < 11.f)
		{
			followPosition = owner->getPosition();
			setPosition(followPosition);
			return;
		}*/
		followPosition = owner->getPosition();
		setPosition(followPosition);
		
		return;
	}
	if (getTarget() == getPosition())
	{
		if (getHunger()<= 0)
			{
				addHunger(0);
				addHealth( - 2);
			}
			else
			{
				addHunger(-10);
			}

		/*std::cout <<"Hunger:" << getHunger() << std::endl;
		std::cout << "Health:" << getHealth() << std::endl;
		std::cout << "Money:" << getMoney() << std::endl;*/
		setTargetTile(GrassTile);
		chooseTarget();
	}

	basicWalk();
	
}

void Dog::fight(Entity* enemy) {
	if (owner)
	{
		if (enemy->getID() == owner->getID())
		{
			//std::cout << "pat pat" << std::endl;
			if (owner->getMoney()>=100 && getHealth()<=50)
			{
				owner->addMoney(-100);
				addHealth(100 - getHealth());
			}
			return;
		}
	}
	if (getType()==enemy->getType())
	{
		//animals play or something
		return;
	}

	if (enemy->getType() == human && rand()%10==0)
	{
		//std::cout << "dog got addopted by" << owner->getID()<<std::endl;
		Human* master = dynamic_cast<Human*>(enemy);
        owner = master;
		owner->addMoney(-100);
		addHealth(100 - getHealth());
		addHunger(100 - getHunger());
	}
	
	for (;;) {

		// there is <=  because of items will add to zero so there is no problem with swiftness 9999 
		if (rand() % 100 <= 0  + enemy->getSwiftness()) {
			enemy->walk();
			break;
		}

		if (rand() % 100 <= 0 + getSwiftness()) {
			walk();
			break;
		}

		enemy->addHealth(-getAttack());
		if (enemy->getHealth() <= 0) {

			break;
		}

		addHealth(-enemy->getAttack());
		if (getHealth() <= 0) {

			break;
		}

		
	}
}

void Dog::hunt() {
	if (rand() % 3 == 0 && getHunger() < 50)
	{
		addHunger((rand() % 10) * 5);
		addHealth(1);//it's enought for a cat to survive
	}
}