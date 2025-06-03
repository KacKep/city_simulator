#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "EnumList.hpp"
#include <iostream>
#include <sstream>

//abstract class that is used for both humans and animals

enum Direction
{
	left = 0,
	down = 1,
	right = 2,
	up = 3,
	neutral = 4

};

class Building;

class Entity : public sf::RectangleShape
{
public:
	Entity();
	virtual ~Entity() = default;

	//------Getters and Seters------------

	//basically everything is private because of hermetization so we have to use those

	//--------------Iteration------------
	void setIteration();
	int getIteration();
	//-----------------Dead---------------------
	void setDead(bool yes);
	bool isDead() const;
	int getDeathCount();
	int getDeathIteration();
	//----------------Drunkness--------------
	int getDrunkness() const; //I prefer getDrunk
	void addDrunkness(int drunkness);
	//----------------Hunger-----------------
	int getHunger() const;
	void addHunger(int hunger);
	//----------------Health----------------
	int getHealth() const;
	void addHealth(int health);
	//----------------Happiness----------------
	int getHappiness() const;
	void addHappiness(int happiness);
	//----------------Education----------------
	int getSemester() const;
	void addSemester(int semester);
	//---------------Attack-----------------
	int getAttack()const;
	void setAttack(int attack);
	//-------------Swiftness----------------
	int getSwiftness()const;
	void setSwiftness(int swiftness);
	//-------------Defence----------------
	int getDefence()const;
	void setDefence(int defence);
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
	//-------------------map set up-------------------
	void setMap(std::vector<std::vector<int>>& map, sf::Vector2i boundry);
	const std::vector<std::vector<int>>& getMap()const;
	const sf::Vector2i& getBoundry ()const;

	//------Type of entity (maps don't exist 100%)----
	void setType(EntityList label);
	EntityList getType()const;

	//------------------methods------------------

	virtual std::string toSave();

	bool checkBoundry(unsigned int distance, Direction direction);

	void chooseTarget();
	//virtual void behavior();

	void walkBasic();
	void walkDrunk();

	bool walkCircle(BuildingList checked_tile);

	bool walkSpecific(BuildingList checked_tile);

	//--------interface methods----------

	virtual void fight(Entity* enemy)=0;
	
	virtual void walk() = 0;

	


private:
	//variables
	bool dead;
	int drunkness;
	int hunger;
	int health;
	int attack;
	int defence;
	int swiftness;
	int happiness;
	int education;
	double money;
	unsigned int ID;
	unsigned int deathIteration;
	//movement related
	Direction dir; //number of the tile where the entity is going
	sf::Vector2f target;
	BuildingList place;	//tile of the buildings mostly
	EntityList entity_type; //0 means human, 1 means animal
	//static variables
	static long unsigned int entity_count;
	static long unsigned int death_count;
	static long unsigned int iteration;
	//map related
	static std::vector<std::vector<int>> map;
	static sf::Vector2i boundry;

	//interface method
	virtual void behavior() = 0;
};

