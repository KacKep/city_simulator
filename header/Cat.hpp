#pragma once
#include "Animal.hpp"
#include "Entity.hpp"

class Cat :public Animal
{
public:
	Cat(Human* owner);
	~Cat()override=default;

private:
	static sf::Texture texture;
	void behavior()override;
};
