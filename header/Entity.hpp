#pragma once
#include "Building.hpp"

class Entity : public sf::RectangleShape
{
public:
	Entity();
	virtual ~Entity() =default;

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

	void setIntMap(std::vector<std::vector<int>>& intmap, static sf::Vector2i boundry);
	std::vector<std::vector<int>>& getIntMap()const;
	const sf::Vector2i& getBoundry ()const;

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
	static std::vector<std::vector<int>> intmap;
	
};

