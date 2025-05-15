#include "Human2.hpp"

Human2::Human2()
	:Entity()
{
	//std::cout << "Texture path: " << std::string(RESOURCE_DIR) + "/brick1.png" << std::endl;
	setID();
	std::cout << "\nID:" << getID();
	if (getID() > 0)
	{
		setTargetTile(PavementTile);
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
	setFillColor(sf::Color::Black);
	//sf::Color(rand() % 256, rand() % 256, rand() % 256, 255)

		setDead(false);
		setType(human);
		setHealth(100);
		setHunger(100);
		setAttack(5);
		setMoney((double)100);
	
}


Human2::~Human2(){
}



//walking
void Human2::walk() {
	if (getDead())
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

	//setFillColor(sf::Color(getFillColor().r % 256, getFillColor().g % 256, getFillColor().b, 255));


	
	
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


void Human2::fight(Entity& enemy) {
	for (;;) {
		
		enemy.setHealth(enemy.getHealth() - getAttack());
		if (enemy.getHealth() <= 0) {

			break;
		}

		setHealth(getHealth() - enemy.getAttack());
		if (getHealth() <= 0) {

			break;
		}
		

		if (rand() % (10 /*- object->item->getAgility()*/) == 0) {
			enemy.walk();
			break;
		}

		if (rand() % 10 == 0) {
			walk();
			break;
		}
	}
}



void Human2::behavior() {

	if (getTarget()==getPosition())
	{
		if (getBoundry().x>9&&getBoundry().y>9)
		{
			if (getHunger() - 10 <= 0)
			{
				setHunger(0);
				setHealth(getHealth() - 2);
			}
			setHunger(getHunger() - 10);
		}
		
		/*std::cout <<"Hunger:" << getHunger() << std::endl;
		std::cout << "Health:" << getHealth() << std::endl;
		std::cout << "Money:" << getMoney() << std::endl;*/
		
		if (getHealth()<40&& getMoney() > 1000)
		{
			setTargetTile(HospitalTile); 
		}
		else if (getHunger() < 50 && getMoney()>150)
		{
			setTargetTile(ShopTile);
		}
		else if (getMoney()<100)
		{
			setTargetTile(OfficeBuildingTile);
		}
		else
		{
			if (rand()%4==0)
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