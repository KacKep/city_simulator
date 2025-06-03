#pragma once
#include "Building.hpp"
//this class inherits basically everything from the building class
//heals humans in exchange for money. there is no free healthcare in this world
class Hospital : public Building
{
public:
	Hospital();
	~Hospital() override = default;


private:

};