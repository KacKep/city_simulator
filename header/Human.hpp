#pragma once
#include "Entity.hpp"
#include"Item.hpp"

class Human : public Entity
{
public:
	Human();
	~Human() override = default;

	//int getAttack()const override;
	void walk() override;
	void fight(Entity* enemy) override;
	std::string toSave()override;


private:
	Item item;
	void behavior()override;
};

