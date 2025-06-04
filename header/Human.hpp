#pragma once
#include "Entity.hpp"
#include"Item.hpp"

///<summary>
/// Human makes most decisions it's the most complex class.
/// It has needs only buildings can help them them
/// </summary>

class Human : public Entity
{
public:
	Human();
	~Human() override = default;
	///overriding methods from the abstract entity class (example of polimorhpism)
	void walk() override;
	void fight(Entity* enemy) override;
	std::string toSave()override;
	std::string getName();
	void setPetID(int petID);
	int getPetID() const;

private:
	//------------variables---------------
	///most variables are just inheritted from the entity class
	Item item; //this is a composition, each human has his own unique item that is directly dependent on him
	static sf::Texture texture;
	std::string name;
	int petID;
	///methods
	void setName();
	///polimorphism
	void behavior()override;
};

