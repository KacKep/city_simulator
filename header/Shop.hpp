#pragma once
#include "Building.hpp"
//this class inherits basically everything from the building class
//humans buy food here if they are hungry
class Shop: public Building 
{
public:
	Shop ();
	~Shop () override = default;


private:

};

