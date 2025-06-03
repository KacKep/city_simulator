#include "Building.hpp"

/**@File Base class for all buildings, all building types inherit from it*/
long unsigned int Building::building_count=0;

Building::Building(const std::string& name, const BuildingList& construct)
	: sf::RectangleShape({ 10,10 }),
	money(0),
	productValue(0),
	price(0),
	name(name),
	ID(0),
	construct(construct)
{
	setID();
}

//-----------setters and getters----------
std::string Building::getName() const {
	return this->name;
}
//----------ID---------
void Building::setID() {
	this->ID = building_count++;
}
int Building::getID() {
	return this->ID;
}

//------------setProductValue-----------
void Building::setProductValue(int value) {
	this->productValue = value;
 }
int Building::getProductValue()const {
	return productValue;
}

//--------------Price---------
void Building::setPrice(int price) {
	this->price = price;
}
int Building::getPrice()const {
	return price;
}

//----------Money---------
void Building::addMoney(double money) {
	this->money += money;
}
double Building::getMoney()const {
	return money;
}

//-----------Tile-------------
int Building::getTile()  {
	return construct;
}

// I'm bob the builder. I will build it if there is a place enough place in city boundrys
bool Building::Build(std::vector<std::vector<int>>& Intmap, int xBoundry, int yBoundry) {

	//std::cout << "Build() called" << std::endl;
	int xMap = rand() % (xBoundry);
	int yMap = rand() % (yBoundry);
	int X2;
	int Y2;
	int xSize = std::round( getSize().y) / 10;
	int ySize = std::round( getSize().x) / 10;
	int xMidSize = xSize / 2;
	int yMidSize = ySize / 2;
	//if (xBoundry<xSize+5||yBoundry<ySize+5)
	//{
	//	std::cout << "No space for the: " << getName() << std::endl;
	//	return false;
	//}
	

	int freeSpaces = 0;
	for (int y = 0; y < yBoundry; ++y) {
		Y2 = (y + yMap) % (yBoundry);
		if (Y2 <= 0 || Y2 + ySize >= yBoundry)
		{
			continue;
		}
		for (int x = 0; x < xBoundry; ++x) {
			X2 = (x + xMap) % (xBoundry  );
			

			
			if (X2 <= 0 || X2 + xSize >= xBoundry)
			{
				continue;
			}
			// looking in corners for PavementTile
			if (Intmap[X2 - 1][Y2 - 1] != PavementTile && Intmap[X2 + xSize][Y2 + ySize] != PavementTile) 
			{ continue; }

			//basic check
			// max left building check
			if (Intmap[X2][Y2] >= PavementTile || Intmap[X2 + xSize - 1][Y2] >= PavementTile) 
			{ continue; } 
			//max right building check
			if (Intmap[X2][Y2 + ySize - 1] >= PavementTile || Intmap[X2 + xSize - 1][Y2 + ySize - 1] >= PavementTile) 
			{continue;}
			
			//"expert" checks
			// middle top and middle bottom check
			if ((Intmap[X2 + xMidSize][Y2] >= PavementTile || Intmap[X2 + xMidSize][Y2 + ySize - 1] >= PavementTile)) 
			{ continue; }

			//middle left and middle right check 
			if (Intmap[X2][Y2 + yMidSize] >= PavementTile || Intmap[X2 + xSize - 1][Y2 + yMidSize] >= PavementTile) 
			{ continue; }  //  now everybode hates me for this as they should but it works lol
	

				//std::cout << "\n1 first check;" << Intmap[X2][Y2] << ", " << Intmap[X2 + xSize - 1][Y2] << ", " <<  // max left building check
				//	"\n2 second check;" << Intmap[X2][Y2 + ySize - 1] << ", " << Intmap[X2 + xSize - 1][Y2 + ySize - 1] << ", " << //max right building check
				//	//"expert" checks
				//	"\n3 xMidSize check;" << Intmap[X2 + xMidSize][Y2] << ", " << Intmap[X2 + xMidSize][Y2 + ySize - 1] << ", " << // middle top and middle bottom check
				//	"\n4  yMidSize check;" << Intmap[X2][Y2 + yMidSize] << ", " << Intmap[X2 + xSize - 1][Y2 + yMidSize] << ", " <<//middle left and middle right check  //  now everybode hates me for this as they should but it works lol
				//	//final check for walkable surface
				//	"\n pevment check;" << Intmap[X2 - 1][Y2 - 1] << ", " << Intmap[X2 + xSize][Y2 + ySize];

				for (int i = 0; i < xSize; ++i) {
					for (int j = 0; j < ySize; ++j) {
						/*if (X2+i <= 0 || X2+i + xSize >= xBoundry||Y2+j <= 0 || Y2+j + ySize >= yBoundry)
						{
							break;
						}*/
						Intmap[X2 + i][Y2 + j] = getTile();
					}
				}
				/*std::cout << "\nXmap" << xMap << " ,Ymap " << yMap
					<< "\nX2:" << X2 << " ,Y2:" << Y2
					<< "\nxMid" << xMidSize << " , yMid" << yMidSize << std::endl;*/



				// i know i'ts confusing 
				this->setPosition(sf::Vector2f(Y2 * 10, X2 * 10));
				return true;
			
		}

		
	}
	//std::cout << "No space for the " << getName() << " (ID: " << getID() << ")" << std::endl;
	return false;
}


