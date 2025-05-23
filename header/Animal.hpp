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
	Human* getOwner() const;
	//when no owner for dogs and allway for cats
	void hunt();

	std::string getName();
	void setName(std::string name);
	//making dog and cat in difffrent object classes and giving them static textures would be better

	std::string toSave()override;
	
	
private:
	void behavior()override;

	std::string name;
	Human* owner;
	
};

