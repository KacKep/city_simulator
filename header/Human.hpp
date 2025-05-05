#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>

class Human : public sf::Drawable, public sf::Transformable {
public:
	// ---------methods-------
	Human(int seed);
	~Human();
	int getSeed();
	sf::Vector2f getPosition();
	void checkBoundry();
	void setTarget(bool a);
	bool getTarget();
	void walk();

	//void draw(sf::RenderWindow& window);
private:
	// ------------values----------
	float xVelocity, yVelocity ;
	sf::RectangleShape shape;
	int seed;
	bool isTarget;
	sf::Vector2f Position;
	sf::Vector2f TargetPosition;


	// ---------methods-------
	void Target();

	//draw override copium
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	/*sf::VertexArray m_vertices;
	sf::Texture     m_tileset;*/

};