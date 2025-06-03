#pragma once
#include "Building.hpp"
//this class inherits basically everything from the building class
//humans earn money here, the more semesters a human has graduated, the more money he earns
class OfficeBuilding : public Building
{
public:
	OfficeBuilding();
	~OfficeBuilding() override = default;


private:

};