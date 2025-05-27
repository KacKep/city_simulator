#include "Human.hpp"

sf::Texture Human::texture(std::string(RESOURCE_DIR) + "/Karol_Wojtyla.png");

Human::Human()
	:Entity()
{
	//std::cout << "Texture path: " << std::string(RESOURCE_DIR) + "/brick1.png" << std::endl;
	setID();
	//std::cout << "\nID:" << getID();
	setName();
	setPetID(0);
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
	setDefence(getDefence() + item.getDefence());
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

	if (getHealth() > 100) {
		addHealth(100 - getHealth());
	}

	if (getHappiness() > 100) {
		addHappiness(100 - getHappiness());
	}

	if (getTarget() == getPosition())
	{
		behavior();
	}

	if ( getBoundry().x < 10 || getBoundry().y < 10)
	{
		walkBasic();
		return;
	}


	if ( checkBoundry(1, left)== false || checkBoundry(1, right)== false || checkBoundry(1, down)== false || checkBoundry(1, up)== false)
	{
		walkBasic();
		return;
	}
	if (getDrunkness() > 5)
	{
		walkDrunk();
	}
	else if (getTargetTile() != PavementTile && walkCircle(getTargetTile()))
	{

	}
	else if (getTargetTile() > RoadTile && walkCircle(getTargetTile()))
	{

	}
	else if (walkSpecific (PavementTile) )
	{

	}
	else if (walkSpecific (RoadTile) )
	{

	}
	else if (walkCircle(PavementTile))
	{

	}
	else
	{
		walkBasic();
	}
	

	return;
}


void Human::fight(Entity* enemy) {
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



void Human::behavior() {
	//check if it's in correct place
	
		// in 9x9 there is no buildings so you probably want to check who survives the longest
		if (getBoundry().x > 9 && getBoundry().y > 9)
		{
			if (getHunger() <= 0)
			{
				addHunger(0);
				addHealth(-2);
				addHappiness(-2);
			}
			else
			{
				addHunger(-10);
				addHappiness(-1);
			}

		}

		/*std::cout <<"Hunger:" << getHunger() << std::endl;
		std::cout << "Health:" << getHealth() << std::endl;
		std::cout << "Money:" << getMoney() << std::endl;*/

	if (getHealth() < 40 && getMoney() > 1500)
	{
		setTargetTile(HospitalTile);
	}
	else if (getHappiness() < 40 && getMoney() > 1000) {
		setTargetTile(LiqourShopTile);
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
		if (rand() % 4 == 0 && getMoney() > 2000 && getSemester() < 7)
		{
			setTargetTile(PolytechnicTile);
		}
		else if (rand() % 4 == 0 && getMoney() > 1000)
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
	//std::cout << "chosen" << std::endl;
	return;
}

std::string Human::toSave() {
	std::stringstream toSave;
	toSave << getID() << ","
	<< getName() << ",";
	if (isDead() == 0 ) {
		toSave << "Alive,";
		if (getPetID()==0) {
			toSave << "No Pets,";
		}
		else {
			toSave << getPetID()<<",";
		}
		toSave<< getHealth() << ","
		<< getHunger() << ","
		<< getHappiness() << ","
		<< getAttack() << ","
		<< getDefence() << ","
		<< getSwiftness() << ","
		<< getSemester() << ","
		<< getMoney() << ","
		<< getDrunkness() << ","
		<<item.getName();
	}
	else {
		toSave << "Dead (Died on iteration " << getDeathIteration() << ")";
	}
	return toSave.str();
}

std::string Human::getName() {
	return name;
}

void Human::setPetID(int petID) {
	this->petID = petID;
}
int Human::getPetID() const {
	return petID;
}


void Human:: setName() {
	static std::vector<std::string> firstNames = {
		"John", "Radomir", "Grzmislaw", "Gniewomir", "Genowefa", "Christopher", "Kunegunda", "Brajan", "Bozydar", "Alfred", "Jessica", "Michel", "Steve", "Zygmunt", "Nikolai","Jerry","Alexander","Ihor","Karol","Denis","Stanislaw","Vladimir","Tim","Stachu"
	};
	static std::vector<std::string> lastNames = {
		"Smith","Pork", "Jobs","Sunbed","Jones","Nowak", "Kowalski", "Jaroszewicz", "Baranowicz", "Prudnicka","Dudek","Shrimpus","Wojtyla","Poniatowski","Bialy","Cheese"
	};
	std::string first = firstNames[std::rand() % firstNames.size()];
	std::string last = lastNames[std::rand() % lastNames.size()];
	this->name = first + " " + last;
	if (name == "Steve Jobs") {
		this->addMoney(100000);
	}
	if (name == "Stanislaw Poniatowski") {
		this->name = "Stanislaw August Poniatowski";
	}
	if (name == "Karol Wojtyla") {
		//Divine protection
		this->setDefence(10);
		setFillColor(sf::Color::White);
		setTexture(&texture);
	}
	if (name == "Stachu Jones") {
		this->setAttack(15);
		addDrunkness(1000);
	}

	if (name == "John Pork") {
		this->setSwiftness(this->getSwiftness()+25);
		setFillColor(sf::Color(255, 105, 180));
	}
	if (name == "Vladimir Bialy") {
		this->addMoney(5000);
		this->setAttack(this->getAttack()+3);
	}
}