#pragma once
#include "Building.hpp"
#include "EnumList.hpp"
#include <iostream>
#include "Item.hpp"

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

	//--------------Iteration------------
	void setIteration(int iteration);
	int getIteration();
	//-----------------Dead---------------------
	void setDead(bool yes);
	bool isDead() const;
	int getDeathCount();
	int getDeathIteration();
	//----------------Drunkness--------------
	int getDrunkness() const; //I prefere getDrunk 
	void addDrunkness(int drunkness);
	//----------------Hunger-----------------
	int getHunger() const;
	void addHunger(int hunger);
	//----------------Health----------------
	int getHealth() const;
	void addHealth(int health);
	//---------------Attack-----------------
	virtual int getAttack()const;
	void setAttack(int attack);
	//-------------Swiftness----------------
	virtual int getSwiftness()const;
	void setSwiftness(int swiftness);
	//---------------Money------------------
	void addMoney(double money);
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

	void basicWalk();

	

	//--------interface methods----------

	virtual void fight(Entity* enemy)=0;
	
	virtual void walk() = 0;

	


private:
	//everyone has some
	
	
	bool dead;
	int drunkness;
	int hunger;
	int health;
	int attack;
	int swiftness;
	double money;
	sf::Vector2f target;
	BuildingList place;
	EntityList entity_type;
	unsigned int ID;
	unsigned int deathIteration;
	static long unsigned int entity_count;
	static long unsigned int building_interaction_count;
	static long unsigned int death_count;
	static long unsigned int iteration;
	static std::vector<std::vector<int>> map;
	static sf::Vector2i boundry;
	virtual void behavior() = 0;
};

