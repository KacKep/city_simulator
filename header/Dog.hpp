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
	void hunt();
protected:
	sf::Texture texture;
	
private:
	void behavior()override;

	
	Human* owner;
	sf::Vector2f followPosition;
};

