#include "Human.hpp"

Human::Human()
	:Entity()
{
	//std::cout << "Texture path: " << std::string(RESOURCE_DIR) + "/brick1.png" << std::endl;
	setID();
	//std::cout << "\nID:" << getID();

	if (getID() > 0)
	{
		chooseTarget();
		setPosition(getTarget());

		/*if (!secrete.loadFromFile(std::string(RESOURCE_DIR) + "/pobrane.png")) {

		}
		else {
			setTexture(&secrete);

		}*/
		setOutlineColor(sf::Color::Black);
		setOutlineThickness(1);
	}
	setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256, 255));


}




//walking
void Human::walk() {
	if (isDead())
	{
		//std::cout <<"\tx:" << getPosition().x << " \ty:" << getPosition().y << std::endl;
		return;
	}
	if (getHealth() <= 0) {
		//std::cout << "human nr " << getID() << " died" << std::endl;
		setDead(true);
		setFillColor(sf::Color::Transparent);
		setOutlineThickness(0);
	}
	behavior();
	basicWalk();

	return;
}


void Human::fight(Entity* enemy) {
	for (;;) {

		// there is <=  becaus item will add to zero so there is no problem with swiftness 9999 
		if (rand() % 10 <= 0) {
			enemy->walk();
			break;
		}

		if (rand() % 10 <= 0) {
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



void Human::behavior() {
	//check if it's in correct place
	if (getTarget() == getPosition())
	{
		// in 9x9 there is no buildings so you probably want to check who survives the longest
		if (getBoundry().x > 9 && getBoundry().y > 9)
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

		}

		/*std::cout <<"Hunger:" << getHunger() << std::endl;
		std::cout << "Health:" << getHealth() << std::endl;
		std::cout << "Money:" << getMoney() << std::endl;*/

		if (getHealth() < 40 && getMoney() > 1500)
		{
			setTargetTile(HospitalTile);
		}
		else if (getHunger() < 50 && getMoney() > 150)
		{
			setTargetTile(ShopTile);
		}
		else if (getMoney() < 100)
		{
			setTargetTile(OfficeBuildingTile);
		}
		else
		{
			if (rand() % 4 == 0 && getMoney() > 1000)
			{
				setTargetTile(LiqourShopTile);
			}
			else if (rand() % 4 == 0)
			{
				setTargetTile(OfficeBuildingTile);
			}
			else
			{
				setTargetTile(PavementTile);
			}

		}
		chooseTarget();

	}
	//if (getTarget()==getPosition() /*|| ++unstuck == (getBoundry().x * getBoundry().y) / 4*/) {
	//	setPosition( getTarget());
	//	//unstuck = 0;
	//	
	//	//setTarget(false);
	//}
}