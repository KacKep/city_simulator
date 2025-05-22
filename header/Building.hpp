#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <cstdlib>
#include "EnumList.hpp"
#include <iostream>
#include <string>
#include <cmath>

class Building : public sf::RectangleShape
{
public:
	Building(const std::string& name, const BuildingList& construct);
	virtual ~Building() = default;
	

	std::string getName() const;

	void setProductValue(int value);
	int getProductValue()const;

	void setPrice(int price);
	int getPrice() const;

	void addMoney(double money);
	double getMoney() const;

	
	int getTile() ;



	 bool Build(std::vector<std::vector<int>>& Intmap, int xBoundry, int yBoundry) ;
	 
private:
	double money;
	int productValue;
	int price;
	std::string name;
	BuildingList construct;
};