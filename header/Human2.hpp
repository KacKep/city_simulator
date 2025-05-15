#pragma once
#include "Entity.hpp"

class Human2 : public Entity
{
public:
	Human2();
	~Human2();

	//void interact(Building& building) override;
	void walk() override;

private:
	void chooseTarget();
};

