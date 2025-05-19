#pragma once
#include "Entity.hpp"
#include "Human.hpp"

class Dog : public Entity
{
public:
	Dog(Human* human);
	~Dog()override;


	void walk() override;
	void fight(Entity* enemy) override;
	Human* getOwner() const;
	//when no owner for dogs and allway for cats
	void hunt();

	std::string getName();
	void setName(std::string name);
protected:
	//making dog and cat in difffrent object classes and giving them static textures would be better
	sf::Texture texture;
	
private:
	void behavior()override;

	std::string name;
	Human* owner;
	sf::Vector2f followPosition;
};

