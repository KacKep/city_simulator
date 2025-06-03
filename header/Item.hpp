#pragma once
#include <string>
#include <cstdlib>
#include <iostream>
class Item
//item class is an example of composition, each instance of this class exists only as an item that an individual human has
{
private:
	std::string name;
	int attack;
	int defence;
	int swiftness;
public:
	Item();
	~Item();
	//getters
	int getAttack1() const;
	int getSwiftness() const;
	int getDefence() const;
	std:: string getName() const;
};

