#pragma once
#include "Entity.hpp"
#include "Human.hpp"


///<summary>
/// an abstract class for all animals
///it is agregated to humans, every animal has a human owner
/// </summary>


class Animal : public Entity
{
public:
	Animal(Human* human);
	~Animal()override;

	///overriding basic methods inherited from the entity class (polimorphism)
	void walk() override;
	void fight(Entity* enemy) override;
	Human* getOwner() const;
	///a way to get food when animal has no owner and always for cats
	void hunt();
	std::string getName();
	void setName(std::string name);
	std::string toSave()override;
	
	
private:
	///most variables are just inheritted from the entity class

	///another example of polimorphism
	void behavior()override;
	///variables
	std::string name;
	Human* owner;
	
};

