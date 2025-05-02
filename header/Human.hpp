#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>

class Human : public sf::Drawable, public sf::Transformable {
public:
	Human(int seed);
	~Human();
	int getSeed();
	sf::Vector2f getPosition();
	void setPosition();
	//void draw(sf::RenderWindow& window);
	void setTarget(bool a);
	bool getTarget();

	void walk();
private:
	void Target();

	float xVelocity, yVelocity ;
	

	sf::RectangleShape shape;
	int seed;
	bool isTarget;
	sf::Vector2f Position;
	sf::Vector2f TargetPosition;

	//draw override copium
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::VertexArray m_vertices;
	sf::Texture     m_tileset;

};