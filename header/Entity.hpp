#pragma once
#include "Building.hpp"
#include "BuildingList.hpp"
#include <iostream>

enum Direction
{
	left=0,
	right=1,
	down=2,
	up=3

};

class Entity : public sf::RectangleShape
{
public:
	Entity();
	virtual ~Entity() =default;

	//------Getters and Seters------------

	void setDead(bool yes);
	bool getDead() const;

	int getHunger() const;
	void setHunger(int hunger);

	int getHealth() const;
	void setHealth(int health);

	virtual int getAttack()const;
	void setAttack(int attack);

	sf::Vector2f getTarget()const;
	void setTarget(sf::Vector2f target);

	void setID();
	unsigned int getID() const;

	unsigned int getEntityCount();

	//------methods------

	void setMap(std::vector<std::vector<int>>& map, static sf::Vector2i boundry);
	const std::vector<std::vector<int>>& getMap()const;
	const sf::Vector2i& getBoundry ()const;

	bool checkBoundry(unsigned int dystance, Direction direction);

	//--------interface methods----------

	/*virtual void fight(Entity& enemy)=0;
	virtual void interact(Building& building) = 0;*/
	virtual void walk() = 0;

	


private:
	bool dead;
	int health;
	int hunger;
	int attack;
	sf::Vector2f target;
	static sf::Vector2i boundry;
	static std::vector<std::vector<int>> map;
	static unsigned int entity_count;
	unsigned int ID;
	
};

