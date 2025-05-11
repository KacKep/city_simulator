#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "BuildingList.hpp"
#include <iostream>
#include <string>
class Building : public sf::Drawable, public sf::Transformable
{
public:
	Building(const std::string& name, const BuildingList& construct);
	~Building() = default;

	virtual sf::Vector2f getPosition()=0;
	virtual void setPosition(sf::Vector2f position) = 0;

	virtual sf::RectangleShape& getShape()=0;

	virtual std::string& getName();
	virtual int getTile() const = 0;

	virtual bool Build(std::vector<std::vector<int>>& Intmap, int xBoundry, int yBoundry) ;

protected:
	std::string name;
	BuildingList construct;
};

