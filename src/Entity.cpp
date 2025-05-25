#include "Entity.hpp"

//it's static and it must be implemented beafor using it so long gaybowser
sf::Vector2i Entity::boundry = { 10,10 };
 std::vector<std::vector<int>> Entity::map;
 long unsigned int Entity::entity_count=0;
 long unsigned int Entity::building_interaction_count =0;
 long unsigned int Entity::death_count=0;
 long unsigned int Entity::iteration=0;

Entity::Entity()
	: sf::RectangleShape({10,10}),
	money(1000),
	health(100),
	hunger(100),
	attack(5),
	defence(0),
	dead(false),
	ID(0),
	entity_type(human),
	drunkness(0),
	place(PavementTile),
	swiftness(0),
	deathIteration(0),
	dir(neutral)
{
	
}
//----------Getters, Seters or Adders------------
//----------------Iteration--------------
void Entity::setIteration(int iteration) {
	this->iteration = iteration;
}
int Entity::getIteration() {
	return this->iteration;
}

//------------------Dead------------------
 bool Entity::isDead() const {
	 return dead;
 }
 void Entity::setDead(bool yes) {	// zmobies won't be comming to the town anytime soon
	 this->dead = yes;
	death_count++;
	this->deathIteration = this->iteration;
	//std::cout << this->deathIteration << " ";
}
int Entity::getDeathCount() {
	return death_count;
}
int Entity::getDeathIteration() {
	return deathIteration;
}
 //----------------Drunkness--------------
 int Entity::getDrunkness() const {
	 return drunkness;
 }
 void Entity::addDrunkness(int drunkness) {
	 this->drunkness += drunkness;
 }
 //----------------Hunger-----------------
 int Entity::getHunger() const {
	 return hunger;
}
 void Entity::addHunger(int hunger) {
	 this->hunger += hunger;
}
 //----------------Health----------------
 int Entity::getHealth() const {
	 return health;
}
 void Entity::addHealth(int health) {
	 this->health += health;
}
 //---------------Attack-----------------
 int Entity::getAttack()const {
	 return attack;
}
 void Entity::setAttack(int attack) {
	 this->attack = attack;
}
 //-------------Swiftness----------------
 int Entity::getSwiftness()const {
	 return swiftness;
 }
 void Entity::setSwiftness(int Swiftness) {
	 this->swiftness = Swiftness;
 }
 //-------------Defence----------------
 int Entity::getDefence()const{
	return defence;
 }
void Entity::setDefence(int defence) {
	this->defence = defence;
}
 //---------------Money------------------
 void Entity::addMoney(double money) {
	 this->money += money;
 }
 double Entity::getMoney()const {
	 return money;
 }
 //--------------Target------------------
 sf::Vector2f Entity::getTarget()const {
	 return target;
 }
 void Entity::setTarget(sf::Vector2f target) {
	 this->target = target;
 }
 //------------Target Tile---------------
 BuildingList Entity::getTargetTile()const {
	 return place;
 }
 void Entity::setTargetTile(BuildingList tile) {
	 this->place = tile;
 }
 //-----------ID and countig--------------
 void Entity::setID() {
	 this->ID = entity_count++;
 }
 unsigned int Entity::getID() const {
	 return ID;
 }
 unsigned int Entity::getEntityCount() {
	return entity_count;
 }
 //------building interaction stats-------
  //I mean it's not wrong but not right either. Btw there is operator overloading in City.cpp at the bottom
 void Entity::interactionCount() {
	 building_interaction_count++;
 }

 const long unsigned int Entity::getBuiildingInteractionCount() {
	 return building_interaction_count;
 }
 //-------------------map set up-------------------
 void Entity::setMap(std::vector<std::vector<int>>& map, sf::Vector2i boundry) {
	 this->map = map;
	 this->boundry = boundry;
 }
 const std::vector<std::vector<int>>& Entity::getMap() const {
	 return map;
 }
 const sf::Vector2i& Entity::getBoundry()const {
	 return boundry;
 }
 //------Type of entity (maps don't exist 100%)----


 void Entity::setType(EntityList label) {
	 this->entity_type = label;
 }

 EntityList Entity::getType() const {
	 return entity_type;
 }


 //------------------methods------------------
 
 //getting data from getters to be saved

std::string Entity::toSave() {
	std::stringstream toSave;
//	toSave << ID << " " << entity_type << " " << dead << " " << health << " " << hunger
//	   << " " << attack << " " << swiftness << " " << money << " " << drunkness;
	return toSave.str();
}


 // choose some target on map but the target(mostly buildings) is decided by behavior wich is contained by the corresponding class
 void Entity::chooseTarget() {
	 dir = neutral;
	 for (size_t i = 0; i < 3; i++)//it only exist for no pavment tiles
	 {


		 //setTarget(sf::Vector2f({ rand() % getBoundry().x, rand() % getBoundry().y }));
		 int xMap = rand() % getBoundry().x;
		 int yMap = rand() % getBoundry().y;
		 int X2;
		 int Y2;
		 for (int y = 0; y < getBoundry().y; y++)
		 {
			 for (int x = 0; x < getBoundry().x; x++)
			 {
				 X2 = (xMap + x) % (getBoundry().x);
				 Y2 = (yMap + y) % (getBoundry().y);
				 if (getMap()[X2][Y2] == getTargetTile()) {
					 //std::cout << "\n Targetx" << getTarget().x << " ,Targety" << getTarget().y;
					 setTarget(sf::Vector2f(Y2 * 10, X2 * 10));
					 //setTarget();
					 return;
				 }
			 }

		 }
		 //fail save if there is no buildings
		 if (i == 0)
		 {
			 setTargetTile(PavementTile);
		 }
		 else
		 {
			 //if there is no road, useful in 9 by 9 map
			 if (rand() % 2 == 0)
			 {
				 setTargetTile(GrassTile);
			 }
			 else
			 {
				 setTargetTile(FlowersTile);
			 }


		 }
	 }
 }

 //checks if the boundry is in given direction. Probably will be used in path finding 
 bool Entity::checkBoundry(unsigned int dystance, Direction direction) {

	 switch (direction) {
	 case left: {
		 //std::cout << check << "- left\n";
		 return (int)getPosition().x / 10 >= dystance;
	 }
	 case right: {
		 //std::cout << check << "- right\n";
		 return (int)getPosition().x / 10 < getBoundry().x - dystance;
	 }
	 case up: {
		 //std::cout << check << "- up\n";
		 return (int)getPosition().y / 10 >= dystance;
	 }
	 case down: {
		 //std::cout << check << "- down\n";
		 return (int)getPosition().y / 10 < getBoundry().y - dystance;
	 }
	 default: {
		 return false;
	 }
	 }
 }

 void Entity::walkBasic() {


	 if (getTarget().x < getPosition().x)//Left
	 {
		 setPosition(sf::Vector2f(getPosition().x - 10.f, getPosition().y));
		 dir = left;

	 }
	 else if (getTarget().x > getPosition().x)//Right
	 {
		 setPosition(sf::Vector2f(getPosition().x + 10.f, getPosition().y));
		 dir = right;
	 }
	 else if (getTarget().y < getPosition().y)//Up
	 {
		 setPosition(sf::Vector2f(getPosition().x, getPosition().y - 10.f));
		 dir = up;
	 }
	 else if (getTarget().y > getPosition().y) //Down
	 {
		 setPosition(sf::Vector2f(getPosition().x, getPosition().y + 10.f));
		 dir = down;
	 }
 }

 void Entity::walkDrunk() {
	 addDrunkness(-5);
	 if (!checkBoundry(1, left) || !checkBoundry(1, right) || !checkBoundry(1, down) || !checkBoundry(1, up))
	 {
		 return;
	 }
	 switch (rand() % 4)
	 {
	 case left: {
		 if (getMap()[(getPosition().y / 10)][(getPosition().x / 10) - 1] <= RoadTile)
		 {
			 setPosition(sf::Vector2f(getPosition().x - 10.f, getPosition().y));
		 }
		 return;
	 }
	 case right: {
		 if (getMap()[(getPosition().y / 10)][(getPosition().x / 10) + 1] <= RoadTile)
		 {
			 setPosition(sf::Vector2f(getPosition().x + 10.f, getPosition().y));
		 }
		 return;
	 }
	 case down: {
		 if (getMap()[(getPosition().y / 10) + 1][(getPosition().x / 10)] <= RoadTile)
		 {
			 setPosition(sf::Vector2f(getPosition().x, getPosition().y + 10.f));
		 }
		 return;
	 }
	 case up: {
		 if (getMap()[(getPosition().y / 10) - 1][(getPosition().x / 10)] <= RoadTile)
		 {
			 setPosition(sf::Vector2f(getPosition().x, getPosition().y - 10.f));
		 }
		 return;
	 }
	 default:
		 return;
	 }
 }


 bool Entity::walkCircle(BuildingList checked_tile) {
	 if ( getMap()[(getPosition().y / 10) + 1][(getPosition().x / 10)] == checked_tile && dir != up) //Down 
	 {
		 setPosition(sf::Vector2f(getPosition().x, getPosition().y + 10.f));
		 dir = down;
		 return true;
	 }
	 else if ( getMap()[(getPosition().y / 10)][(getPosition().x / 10) + 1] == checked_tile && dir != left)//Right
	 {
		 setPosition(sf::Vector2f(getPosition().x + 10.f, getPosition().y));
		 dir = right;
		 return true;
	 }
	 else if ( getMap()[(getPosition().y / 10) - 1][(getPosition().x / 10)] == checked_tile && dir != down)//UP
	 {
		 setPosition(sf::Vector2f(getPosition().x, getPosition().y - 10.f));
		 dir = up;
		 return true;
	 }
	 else if ( getMap()[(getPosition().y / 10)][(getPosition().x / 10) - 1] == checked_tile && dir != right)//Left
	 {
		 setPosition(sf::Vector2f(getPosition().x - 10.f, getPosition().y));
		 dir = left;
		 return true;
	 }
	 
	 return false;
 }

 bool Entity::walkSpecific(BuildingList checked_tile) {
	 if (getTarget().y > getPosition().y && getMap()[(getPosition().y / 10) + 1][(getPosition().x / 10)] == checked_tile && dir != up) //Down 
	 {
		 setPosition(sf::Vector2f(getPosition().x, getPosition().y + 10.f));
		 dir = down;
		 //std::cout << "down" << std::endl;
		 return true;
	 }
	 else if (getTarget().x > getPosition().x && getMap()[(getPosition().y / 10)][(getPosition().x / 10) + 1] == checked_tile && dir != left)//Right
	 {
		 setPosition(sf::Vector2f(getPosition().x + 10.f, getPosition().y));
		 dir = right;
		 //std::cout << "right" << std::endl;
		 return true;
	 }
	 else if (getTarget().y < getPosition().y && getMap()[(getPosition().y / 10) - 1][(getPosition().x / 10)] == checked_tile && dir != down)//UP
	 {
		 setPosition(sf::Vector2f(getPosition().x, getPosition().y - 10.f));
		 dir = up;
		 //std::cout << "up" << std::endl;
		 return true;
	 }
	 else if (getTarget().x < getPosition().x && getMap()[(getPosition().y / 10)][(getPosition().x / 10) - 1] == checked_tile && dir != right)//Left
	 {
		 setPosition(sf::Vector2f(getPosition().x - 10.f, getPosition().y));
		 dir = left;
		 //std::cout << "left" << std::endl;
		 return true;
	 }
	 return false;
 }
