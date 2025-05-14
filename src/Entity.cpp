#include "Entity.hpp"
//it's static and it must be implemented beafor using it so long gaybowser
sf::Vector2i Entity::boundry = { 10,10 };
 std::vector<std::vector<int>> Entity::map;
 unsigned int Entity::entity_count=0;

Entity::Entity()
	: sf::RectangleShape({10,10}){}

 bool Entity::getDead() const {
	 return dead;
 }
 void Entity::setDead(bool yes) {
	 this->dead = yes;
}
 
 int Entity::getHunger() const {
	 return hunger;
}
 void Entity::setHunger(int hunger) {
	 this->hunger = hunger;
}

 int Entity::getHealth() const {
	 return health;
}
 void Entity::setHealth(int health) {
	 this->health = health;
}

 int Entity::getAttack()const {
	 return attack;
}
 void Entity::setAttack(int attack) {
	 this->attack = attack;
}

 sf::Vector2f Entity::getTarget()const {
	 return target;
}
 void Entity::setTarget(sf::Vector2f target) {
	 this->target = target;
}

 void Entity::setID() {
	 this->ID = entity_count++;
 }
 unsigned int Entity::getID() const {
	 return ID;
 }
 unsigned int Entity::getEntityCount() {
	return entity_count;
 }

 //--------methods-------
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

 void Entity::setMap(std::vector<std::vector<int>>& map, static sf::Vector2i boundry) {
	 this->map = map;
	 this->boundry = boundry;
}
 const std::vector<std::vector<int>>& Entity::getMap() const {
	 return map;
 }
 const sf::Vector2i& Entity::getBoundry()const {
	 return boundry;
 }

 //if (TargetPosition.x < getPosition().x)
 //{
	// setPosition(sf::Vector2f(getPosition().x - 10.f, getPosition().y));

 //}
 //else if (TargetPosition.x > getPosition().x) {
	// setPosition(sf::Vector2f(getPosition().x + 10.f, getPosition().y));
 //}
 //else if (TargetPosition.y < getPosition().y)
 //{
	// setPosition(sf::Vector2f(getPosition().x, getPosition().y - 10.f));
 //}
 //else if (TargetPosition.y > getPosition().y) {
	// setPosition(sf::Vector2f(getPosition().x, getPosition().y + 10.f));
 //}