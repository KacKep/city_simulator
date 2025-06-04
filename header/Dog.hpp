#pragma once
#include "Animal.hpp"

///<summary>
///Dog is a companion of a Human. It will follow the human constantly and die if left alone for too long.
/// </summary>
class Dog :public Animal
{
public:
	Dog(Human* owner);
	~Dog()override = default;

private:
	///this class inherits basically everything from animal, overrides its behaviour
	static sf::Texture texture;
	///unique variable for the dog, that allows it to follow the human
	sf::Vector2f followPosition;
	///polimorphism
	void behavior()override;

};