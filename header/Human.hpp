#pragma once
#include "Entity.hpp"

class Human : public Entity
{
public:
	Human();
	~Human() override = default;

	
	void walk() override;
	void fight(Entity* enemy) override;
private:
	sf::Texture secrete;
	void behavior();
};

