#pragma once
#include "Building.hpp"
///<summary>
/// this class inherits basically everything from the building class
///heals humans in exchange for money. there is no free healthcare in this world
/// </summary>
class Hospital : public Building
{
public:
	Hospital();
	~Hospital() override = default;


private:

};