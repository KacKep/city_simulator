#pragma once
#include <string>
#include <cstdlib>
#include <iostream>
class Item

///<summary>
/// item class is an example of composition, each instance of this class exists only as an item that an individual human has
/// used by humans to fight or protect themselves
///This is an example of composition, each instance of this class exists only as an item that an individual human has
/// </summary>
{
private:
	std::string name;
	int attack;
	int defence;
	int swiftness;
public:
	Item();
	~Item();
	///getters
	int getAttack1() const;
	int getSwiftness() const;
	int getDefence() const;
	std:: string getName() const;
};

