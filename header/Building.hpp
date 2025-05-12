#pragma once

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "BuildingList.hpp"
#include <iostream>
#include <string>
class Building : public sf::RectangleShape
{
public:
	Building(const std::string& name, const BuildingList& construct);
	~Building() = default;
	

	std::string getName() const;
	void setProductValue(int value);

	void setMoney(int money);

	int giveProdactValue() ;
	int getTile() ;



	 bool Build(std::vector<std::vector<int>>& Intmap, int xBoundry, int yBoundry) ;

private:
	double money;
	int productValue;
	std::string name;
	BuildingList construct;
};