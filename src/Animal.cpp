#include "Animal.hpp"

Animal::Animal(Human* human)
	:Entity(),
	owner(human), //that's the only way, said the yt guy about agregations (he was talking about using refrence in the constructor)
	name("Animal")
{
	setID();
	setTarget(owner->getTarget());
	setPosition(getTarget());
	setType(animal);
	
}

std::string Animal::getName() {
	return name;
}

void Animal::setName(std::string name) {
	this->name = name;
}

Animal::~Animal() {
	owner = nullptr;
}

Human* Animal::getOwner() const 
{ return owner; }


//walking
void Animal::walk() {
	if (isDead())
	{
		return;
	}
	

	if (getHealth() <= 0) {
		//std::cout << "animal nr " << getID() << " died" << std::endl;
		setDead(true);
		setFillColor(sf::Color::Transparent);
		setOutlineThickness(0);
	}
	behavior();



	return;
}

void Animal::behavior() {
	if (getTarget() == getPosition())
	{
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
		chooseTarget();
	}

	//walkBasic();
	
}

void Animal::fight(Entity* enemy) {
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

	if (enemy->getType() == human && rand() % 10==0)
	{
		//std::cout << "dog got addopted by" << owner->getID()<<std::endl;
		Human* new_owner = dynamic_cast<Human*>(enemy);
        owner = new_owner;
		if (owner->getMoney()>100)
		{
			owner->addMoney(-100);
			addHealth(100 - getHealth());
			addHunger(100 - getHunger());
		}
		return;
	}
	
	for (;;) {

		// there is <=  because of items will add to zero so there is no problem with swiftness 9999 
		if (rand() % 100 <= 0  + enemy->getSwiftness()) {
			//enemy->walk();
			break;
		}

		if (rand() % 100 <= 0 + getSwiftness()) {
			//walk();
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

void Animal::hunt() {
	if (rand() % 3 == 0 && getHunger() < 50)
	{
		addHunger((rand() % 10) * 5);
		addHealth(1);//it's enought for a cat to survive
	}
}