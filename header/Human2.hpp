#pragma once
#include "Entity.hpp"

class Human2 : public Entity
{
public:
	Human2();
	~Human2();

	
	void walk() override;
	void fight(Entity& enemy) override;
private:
	sf::Texture secrete;
	void behavior();
};

