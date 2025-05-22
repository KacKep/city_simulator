#include "Human.hpp"

Human::Human()
	:Entity(),
	circle_timer(0)
{
	//std::cout << "Texture path: " << std::string(RESOURCE_DIR) + "/brick1.png" << std::endl;
	setID();
	//std::cout << "\nID:" << getID();

	if (getID() > 0)
	{
		chooseTarget();
		setPosition(getTarget());
		setOutlineColor(sf::Color::Black);
		setOutlineThickness(1);
	}
	setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256, 255));
	//std::cout << item.getAttack1() << std::endl;
	setAttack(getAttack() + item.getAttack1());
	setSwiftness(getSwiftness() + item.getSwiftness());
	//setPosition(sf::Vector2f(10, 10));
	
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

	if (getTarget() == getPosition())
	{
		behavior();
	}

	if (getDrunkness()>5)
	{
		walkDrunk();
		return;
	}
	else if (!checkBoundry(1, left) || !checkBoundry(1, right) || !checkBoundry(1, down) || !checkBoundry(1, up)||getTargetTile()<=1)
	{
		walkBasic();
	}
	else if (getTargetTile() > RoadTile && walkCircle(getTargetTile()))
	{

	}
	else if (--circle_timer>0)
	{
		if (!walkCircle(PavementTile))
		{
			walkBasic();
		}
		
	}
	else if (walkSpecific (PavementTile) )
	{
		
	}
	else if (walkSpecific (RoadTile) ) {
		
	}
	else if (circle_timer <= 0)
	{
		circle_timer = 6;
	}
	else
	{
		walkBasic();
	}
	

	return;
}


void Human::fight(Entity* enemy) {
	for (;;) {

		// there is <=  becaus item will add to zero so there is no problem with swiftness 9999 
		if (rand() % 100 <= 0+enemy->getSwiftness()) {
			//enemy->walk();
			break;
		}

		if (rand() % 100 <= 0+ getSwiftness()) {
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



void Human::behavior() {
	//check if it's in correct place
	
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


	
	//if (getTarget()==getPosition() /*|| ++unstuck == (getBoundry().x * getBoundry().y) / 4*/) {
	//	setPosition( getTarget());
	//	//unstuck = 0;
	//	
	//	//setTarget(false);
	//}
}