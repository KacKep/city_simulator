#pragma once
#include <string>
#include <cstdlib>
#include <iostream>
class Item
{
private:
	std::string name;
	int attack;
	int swiftness;
public:
	Item();
	~Item();
	int getAttack1() const;
	int getSwiftness() const;
};

