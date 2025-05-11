#pragma once
#include "Building.hpp"

class Shop: public Building 
{
public:
	Shop ();
	~Shop ();

	sf::Vector2f getPosition() override;
	void setPosition(sf::Vector2f position) override;
	sf::RectangleShape& getShape() override;

	std::string& getName() override;

	int getTile() const override;
	
	//bool Shop::Build(std::vector<std::vector<int>>& Intmap, int xBoundry, int yBoundry)override;

private:
	//std::string name;
	int satiety;
	int price;
	sf::RectangleShape shape;
	sf::Vector2f Position;
	double money;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

