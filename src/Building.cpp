#include "Building.hpp"

Building::Building(const std::string& name, const BuildingList& construct)
	: sf::RectangleShape({ 10,10 }),
	money(0),
	productValue(0),
	price(0),
	name(name),
	construct(construct)
{}//to do: put price and produktVal as constructor initializer or whatever it is

//-----------setters and getters----------
std::string Building::getName() const {
	return this->name;
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

//----------money---------
void Building::setMoney(double money) {
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
	unsigned int xMap = rand() % (xBoundry);
	unsigned int yMap = rand() % (yBoundry);
	int X2;
	int Y2;
	int xSize = getSize().y / 10;
	int ySize = getSize().x / 10;
	int xMidSize = xSize / 2;
	int yMidSize = ySize / 2;
	if (xBoundry<xSize+5||yBoundry<ySize+5)
	{
		std::cout << "No space for the: " << getName() << std::endl;
		return false;
	}
	

	int freeSpaces = 0;
	for (int y = 0; y < yBoundry; ++y) {
		for (int x = 0; x < xBoundry; ++x) {
			X2 = (x + xMap) % (xBoundry - xSize - 2)+1;
			Y2 = (y + yMap) % (yBoundry - ySize - 2)+1;

			if (Y2 <= 0 || Y2 + ySize >= yBoundry)
			{
				break;
			}
			if (X2 <= 0 || X2 + xSize >= xBoundry)
			{
				continue;
			}

			//basic check
			if (X2 > 0 && X2 + xSize < xBoundry && Y2 > 0 && Y2 + ySize < yBoundry && // just chechikng for boundry if % doesn't work
				Intmap[X2][Y2] < PavementTile && Intmap[X2 + xSize - 1][Y2] < PavementTile && // max left building check
				Intmap[X2][Y2 + ySize - 1] < PavementTile && Intmap[X2 + xSize - 1][Y2 + ySize - 1] < PavementTile && (//max right building check
					//"expert" checks
					((xSize > 3) ? (Intmap[X2 + xMidSize][Y2] < PavementTile && Intmap[X2 + xMidSize][Y2 + ySize - 1] < PavementTile) : true) &&// middle top and middle bottom check
					((ySize > 3) ? (Intmap[X2][Y2 + yMidSize] < PavementTile && Intmap[X2 + xSize - 1][Y2 + yMidSize] < PavementTile) : true) && //middle left and middle right check  //  now everybode hates me for this as they should but it works lol
					//final check for walkable surface
					Intmap[X2 - 1][Y2 - 1] == PavementTile || Intmap[X2 + xSize][Y2 + ySize] == PavementTile)) { // looking in corners for PavementTile

				if (Intmap[X2+xMidSize][Y2 + yMidSize] >= PavementTile && Intmap[X2 + xMidSize][Y2 + yMidSize] >= PavementTile)
				{
					continue;
				}

				std::cout << "\n1 first check;" << Intmap[X2][Y2] << ", " << Intmap[X2 + xSize - 1][Y2] << ", " <<  // max left building check
					"\n2 second check;" << Intmap[X2][Y2 + ySize - 1] << ", " << Intmap[X2 + xSize - 1][Y2 + ySize - 1] << ", " << //max right building check
					//"expert" checks
					"\n3 xMidSize check;" << Intmap[X2 + xMidSize][Y2] << ", " << Intmap[X2 + xMidSize][Y2 + ySize - 1] << ", " << // middle top and middle bottom check
					"\n4  yMidSize check;" << Intmap[X2][Y2 + yMidSize] << ", " << Intmap[X2 + xSize - 1][Y2 + yMidSize] << ", " <<//middle left and middle right check  //  now everybode hates me for this as they should but it works lol
					//final check for walkable surface
					"\n pevment check;" << Intmap[X2 - 1][Y2 - 1] << ", " << Intmap[X2 + xSize][Y2 + ySize];

				for (int i = 0; i < xSize; ++i) {
					for (int j = 0; j < ySize; ++j) {
						if (X2+i <= 0 || X2+i + xSize >= xBoundry||Y2+j <= 0 || Y2+j + ySize >= yBoundry)
						{
							break;
						}
						Intmap[X2 + i][Y2 + j] = getTile();
					}
				}
				std::cout << "\nXmap" << xMap << " ,Ymap " << yMap
					<< "\nX2:" << X2 << " ,Y2:" << Y2;



				// i know i'ts confusing but just resources/Vector_shenanigens.png open for explenation
				this->setPosition(sf::Vector2f(Y2 * 10, X2 * 10));
				return true;
			}
		}

		
	}
	std::cout << "No space for the: " << getName() << std::endl;
	return false;
}


