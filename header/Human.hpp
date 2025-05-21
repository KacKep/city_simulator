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

private:
	int circle_timer;
	Item item;
	void behavior()override;
	sf::Texture secrete;
	

};

