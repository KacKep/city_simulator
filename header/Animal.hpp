#pragma once
#include "Entity.hpp"
#include "Human.hpp"

class Animal : public Entity
{
public:
	Animal(Human* human);
	~Animal()override;


	void walk() override;
	void fight(Entity* enemy) override;
private:
	sf::Texture texture;
	void behavior();
	Human* owner;
	sf::Vector2f followPosition;
};

