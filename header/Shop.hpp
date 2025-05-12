#pragma once
#include "Building.hpp"

class Shop: public Building 
{
public:
	Shop ();
	~Shop ();


private:
	
	int foodValue;
	int price;
	

};

