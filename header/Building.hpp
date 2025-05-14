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
	Building();

	std::string getName() const;

	void setProductValue(int value);
	int getProdactValue();

	void setPrice(int price);
	int getPrice();

	void setMoney(double money);
	double getMoney();

	
	int getTile() ;



	 bool Build(std::vector<std::vector<int>>& Intmap, int xBoundry, int yBoundry) ;

private:
	double money;
	int productValue;
	int price;
	std::string name;
	BuildingList construct;
};