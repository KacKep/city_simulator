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
	//-----------------Dead---------------------
	void setDead(bool yes);
	bool isDead() const;
	//----------------Hunger-----------------

	int getHunger() const;
	void setHunger(int hunger);
	//----------------Health----------------
	int getHealth() const;
	void setHealth(int health);
	//---------------Attack-----------------
	virtual int getAttack()const;
	void setAttack(int attack);
	//---------------Money------------------
	void setMoney(double money);
	double getMoney()const;
	//--------------Target------------------
	sf::Vector2f getTarget()const;
	void setTarget(sf::Vector2f target);
	//------------Target Tile---------------
	BuildingList getTargetTile()const;
	void setTargetTile(BuildingList tile);
	//-----------ID and countig--------------
	void setID();
	unsigned int getID() const;
	unsigned int getEntityCount();

	//------building interaction stats-------
	void interactionCount();
	const long unsigned int getBuiildingInteractionCount();
	//-------------------map set up-------------------
	void setMap(std::vector<std::vector<int>>& map, sf::Vector2i boundry);
	const std::vector<std::vector<int>>& getMap()const;
	const sf::Vector2i& getBoundry ()const;

	//------Type of entity (maps don't exist 100%)----
	void setType(EntityList label);
	EntityList getType()const;

	//------------------methods------------------

	bool checkBoundry(unsigned int dystance, Direction direction);

	void chooseTarget();
	//virtual void behavior();


	//--------interface methods----------

	virtual void fight(Entity* enemy)=0;
	
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

