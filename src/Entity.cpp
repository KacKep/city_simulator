#include "Entity.hpp"
//it's static and it must be implemented beafor using it so long gaybowser
sf::Vector2i Entity::boundry = { 10,10 };
 std::vector<std::vector<int>> Entity::map;
 unsigned int Entity::entity_count=0;
 long unsigned int Entity::building_interaction_count =0;
 

Entity::Entity()
	: sf::RectangleShape({10,10}),
	money(1000),
	health(100),
	hunger(100),
	attack(5),
	dead(false)
{}
//----------Getters and Seters------------
//------------------Dead------------------
 bool Entity::isDead() const {
	 return dead;
 }
 void Entity::setDead(bool yes) {
	 this->dead = yes;
}
 //----------------Hunger-----------------
 int Entity::getHunger() const {
	 return hunger;
}
 void Entity::setHunger(int hunger) {
	 this->hunger += hunger;
}
 //----------------Health----------------
 int Entity::getHealth() const {
	 return health;
}
 void Entity::setHealth(int health) {
	 this->health += health;
}
 //---------------Attack-----------------
 int Entity::getAttack()const {
	 return attack;
}
 void Entity::setAttack(int attack) {
	 this->attack = attack;
}
 //---------------Money------------------
 void Entity::setMoney(double money) {
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
 
 

 // choose some target on map but the target(mostly buildings) is decided by behavior wich is contained by the corresponding class
 void Entity::chooseTarget() {
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
					 //std::cout << "\n Targetx" << TargetPosition.x << " ,Targety" << TargetPosition.y;
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
	 case left: // Left
		 //std::cout << check << "- left\n";
		 return (int)getPosition().x / 10 > dystance + 1;
	 case right: // Right
		 //std::cout << check << "- right\n";
		 return (int)getPosition().x / 10 < getBoundry().x - dystance - 1;
	 case up: // Up
		 //std::cout << check << "- up\n";
		 return (int)getPosition().y / 10 > dystance + 1;
	 case down: // Down
		 //std::cout << check << "- down\n";
		 return (int)getPosition().y / 10 < getBoundry().y - dystance - 1;
	 default:
		 return false;
	 }
 }