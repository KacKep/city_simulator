#pragma once
#include "Building.hpp"
#include "EnumList.hpp"
#include <iostream>

enum Direction
{
	left=0,
	right=1,
	down=2,
	up=3

};

class Building;

class Entity : public sf::RectangleShape
{
public:
	Entity();
	virtual ~Entity() = default;

	//------Getters and Seters------------

	void setDead(bool yes);
	bool getDead() const;

	int getHunger() const;
	void setHunger(int hunger);

	int getHealth() const;
	void setHealth(int health);

	virtual int getAttack()const;
	void setAttack(int attack);

	void setMoney(double money);
	double getMoney()const;

	sf::Vector2f getTarget()const;
	void setTarget(sf::Vector2f target);

	BuildingList getTargetTile()const;
	void setTargetTile(BuildingList tile);

	void setID();
	unsigned int getID() const;
	unsigned int getEntityCount();

	//it's more like a counting method at this point
	void interact();
	const long unsigned int getBuiildingInteractionCount();

	void setMap(std::vector<std::vector<int>>& map, sf::Vector2i boundry);
	const std::vector<std::vector<int>>& getMap()const;
	const sf::Vector2i& getBoundry ()const;


	void setType(EntityList label);
	EntityList getType()const;

	//------methods------

	bool checkBoundry(unsigned int dystance, Direction direction);

	void chooseTarget();
	//virtual void behavior();


	//--------interface methods----------

	virtual void fight(Entity& enemy)=0;
	
	virtual void walk() = 0;

	


private:
	
	bool dead;
	int health;
	int hunger;
	int attack;
	double money;
	BuildingList place;
	EntityList entity_type;
	sf::Vector2f target;
	static sf::Vector2i boundry;
	static std::vector<std::vector<int>> map;
	static unsigned int entity_count;
	static long unsigned int building_interaction_count;
	unsigned int ID;

	
};

