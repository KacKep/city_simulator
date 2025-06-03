#include "Animal.hpp"

/**@file Base abstract class for all animals */

Animal::Animal(Human* human)
	:Entity(),
	owner(human), //this is an aggregation, each animal has one human as its owner
	name("Animal")
{
	//sets an unique ID number
	setID();
	//gives the owner the ID of the pet (for saving purposes later)
	owner->setPetID(getID());
	//animal at the start has the same target as its owner
	setTarget(owner->getTarget());
	setPosition(getTarget());
	setType(animal);
	//animals dont use money
	addMoney(-getMoney());
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
	//making sure those nubmers dont exceed 100
	if (getHealth() > 100) {
		addHealth(100 - getHealth());
	}
	if (getHappiness() > 100) {
		addHappiness(100 - getHappiness());
	}
	behavior();



	return;
}

void Animal::behavior() {
	//what happens when the animal gets to their desired target
	if (getTarget() == getPosition())
	{
		//if the hunger is 0, the animal starts to take damage
		if (getHunger() <= 0)
		{
			addHunger(0);
			addHealth(-2);
			addHappiness(-2);
		}
		else
		{
			//if the animal isnt staving, the hunger decreases as well as happiness
			addHunger(-10);
			addHappiness(-1);
		}
	
		setTargetTile(GrassTile);
		chooseTarget();
	}

	//walkBasic();
	
}
//interaction between an animal and another entity
void Animal::fight(Entity* enemy) {
	if (owner)
	{
		//if the animal meets its owner it gets healed (if the owner has money) and gets a lot of happiness (the owner also gets happiness)
		if (enemy->getID() == owner->getID())
		{
			//std::cout << "pat pat" << std::endl;
			addHappiness((rand() % 5 + 1) * 10);
			owner->addHappiness((rand() % 5 + 1) * 5);
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
		//if the enemy is another animal, the animals play or something instead of fighting
		addHappiness((rand() % 5 + 1) * 5);
		return;
	}
	//if the other entity is a human it can adopt the animal if its precious owner died
	if (enemy->getType() == human && rand() % 10==0 && owner->isDead())
	{
		//PREVIOUS OWNER LOSES THE PET
		owner->setPetID(0);
		//PET GETS A NEW OWNER
		Human* new_owner = dynamic_cast<Human*>(enemy);
        owner = new_owner;
		owner->setPetID(getID());
		//the new owner can then heal the animal
		if (owner->getMoney()>100)
		{
			owner->addMoney(-100);
			addHealth(100 - getHealth());
			addHunger(100 - getHunger());
			addHappiness(100 - getHappiness());
		}
		return;
	}
	// if the entity is hostile, fighting commences
	int entity1DefRoll;
	int enemyDefRoll;
	for (;;) {

		// there is <=  becaus item will add to zero so there is no problem with swiftness 9999
		// Check if enemy escapes based on swiftness
		if (rand() % 100 <= enemy->getSwiftness()) {
			break;
		}

		//same for the other entity
		if (rand() % 100 <= getSwiftness()) {
			break;
		}

		// Entity1 attacks entity 2, damage is reduced by a random number from 0 to enemy defence
		enemyDefRoll = rand() % (enemy->getDefence() + 1);
		if (getAttack() > enemyDefRoll) {
			enemy->addHealth(-getAttack() + enemyDefRoll);
		}

		// Check if enemy is dead
		if (enemy->getHealth() <= 0) {
			break;
		}

		// Enemy retaliates
		entity1DefRoll = rand() % (getDefence() + 1);
		if (enemy->getAttack() > entity1DefRoll) {
			addHealth(-enemy->getAttack() + entity1DefRoll);
			addHappiness(-enemy->getAttack());
		}

		if (getHealth() <= 0) {
			break;
		}

		
	}
}
//this method is used for the animals to get food, because they dont go to shops
void Animal::hunt() {
	if (rand() % 3 == 0 && getHunger() < 50)
	{
		addHunger((rand() % 10) * 5);
		addHappiness(10);
		addHealth(1);//it's enought for a cat to survive
	}
}
//all of the data from the getters gets converted to a string that can be printed in the output file
std::string Animal::toSave() {
	std::stringstream toSave;
	toSave << getID() << ","
	<<getName() << ",";
	if (getOwner()->isDead()) {
		toSave<< "Owner is Dead,";
	}
	else {
		toSave<< getOwner()->getID() << ",";
	}
	if (isDead() == 0 ) {
		toSave << "Alive," << getHealth() << ","
		<< getHunger() << ","
		<< getHappiness() << ","
		<< getAttack() << ","
		<< getDefence() << ","
		<< getSwiftness();
	}
	else {
		toSave << "Dead (Died on iteration " << getDeathIteration() << ")";
	}
	return toSave.str();
}