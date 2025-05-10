#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>


class Human : public sf::Drawable, public sf::Transformable {
public:
	// ---------methods-------
	Human(sf::Vector2f a);
	~Human();
	
	sf::Vector2f getPosition();
	bool checkBoundry();
	void setTarget(bool a);
	bool ActiveTarget();
	void walk (const std::vector<std::vector<int>>& Intmap);

	//void draw(sf::RenderWindow& window);
private:
	// ------------values----------
	float xVelocity, yVelocity ;
	sf::RectangleShape shape;
	sf::Vector2f seed;
	bool isTarget;
	sf::Vector2f Position;
	sf::Vector2f TargetPosition;
	int xMap;
	int yMap;
	sf::Vector2f boundry;
	float X2;
	float Y2;
	int unstuck;

	// ---------methods-------
	void Target(const std::vector<std::vector<int>>& Intmap);

	//draw override copium
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	/*sf::VertexArray m_vertices;
	sf::Texture     m_tileset;*/

};