#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <cstdlib>
#include "EnumList.hpp"
#include <iostream>
#include <string>
#include <cmath>

//Base class for all buildings, all building types inherit from it

class Building : public sf::RectangleShape
{
public:
	Building(const std::string& name, const BuildingList& construct);
	virtual ~Building() = default;

	//ID
	void setID();
	int getID();
	//name
	std::string getName() const;
	//product value
	void setProductValue(int value);
	int getProductValue()const;
	//the price
	void setPrice(int price);
	int getPrice() const;
	//money stored in the building
	void addMoney(double money);
	double getMoney() const;

	
	int getTile() ;



	 bool Build(std::vector<std::vector<int>>& Intmap, int xBoundry, int yBoundry) ;
	 
private:
	//money stored in the building, deposited each time an entity buys something, or earned passively by the office if an entity works in it
	double money;
	//product value which determines how effective the product is. For hospitals, grocery and liquor shops it determines how much health, hunger and drunkness respectively its product is going to give, while for the polytechnic it determines how much happiness the student is going to retain after attending one semester
	int productValue;
	//the amount of money the product or service costs
	int price;
	//unique ID
	unsigned int ID;
	static long unsigned int building_count;
	std::string name;
	BuildingList construct;
};