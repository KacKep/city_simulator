#pragma once
#include "Animal.hpp"

//Animal created to show it living with an owner but not chasing it like a dog
//inherits basically everything from the animal class except overriding the behaviour and having a custom texture

class Cat :public Animal
{
public:
	Cat(Human* owner);
	~Cat()override=default;

private:
	static sf::Texture texture;
	//polimorphism
	void behavior()override;
};
