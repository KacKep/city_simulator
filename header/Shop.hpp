#pragma once
#include "Building.hpp"

/// <summary>
/// this class inherits basically everything from the building class
///humans buy food here if they are hungry
/// </summary>
class Shop: public Building 
{
public:
	Shop ();
	~Shop () override = default;


private:

};

