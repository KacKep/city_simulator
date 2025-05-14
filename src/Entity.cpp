#include "Entity.hpp"
//it's static and it must be implemented beafor using it so long gaybowser
sf::Vector2i Entity::boundry = { 10,10 };
 std::vector<std::vector<int>> Entity::intmap;

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

 void Entity::setIntMap(std::vector<std::vector<int>>& intmap, static sf::Vector2i boundry) {
	 this->intmap = intmap;
	 this->boundry = boundry;
}
 std::vector<std::vector<int>>& Entity::getIntMap() const {
	 return intmap;
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