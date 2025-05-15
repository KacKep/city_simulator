#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include "EnumList.hpp"


class Human : public sf::Drawable, public sf::Transformable {
public:
	// ---------methods-------
	Human(sf::Vector2f a);
	~Human();
	
	sf::Vector2f getPosition();
	
	void setTarget(bool a);
	bool ActiveTarget();
	void walk (const std::vector<std::vector<int>>& Intmap);

	//void draw(sf::RenderWindow& window);
private:
	// ------------values----------
	float xVelocity, yVelocity ;
	sf::RectangleShape shape;
	bool isTarget;
	sf::Vector2f Position;
	sf::Vector2f TargetPosition;
	int xMap;
	int yMap;
	sf::Vector2f boundry;
	float X2;
	float Y2;
	int unstuck;
	int hunger;

	// ---------methods-------
	void Target(const std::vector<std::vector<int>>& Intmap);

	bool checkBoundry(unsigned int a,int check);

	void BasicWalk();
	//draw override copium
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


};