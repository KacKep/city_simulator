#pragma once
#include "Animal.hpp"

class Dog :public Animal
{
public:
	Dog(Human* owner);
	~Dog()override = default;

private:

	static sf::Texture texture;
	sf::Vector2f followPosition;
	void behavior()override;

};