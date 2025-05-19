#pragma once
#include "Dog.hpp"
#include "Entity.hpp"

class Cat :public Dog
{
public:
	Cat(Human* owner);
	~Cat()override=default;

private:
	void behavior()override;
};
