#pragma once
#include "Animal.hpp"
#include "Entity.hpp"

class Dog :public Animal
{
public:
	Dog(Human* owner);
	~Dog()override = default;

private:

	static sf::Texture texture;
	sf::Vector2f followPosition;
	int circle_timer;
	void behavior()override;

};