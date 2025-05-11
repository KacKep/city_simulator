#include "Building.hpp"

Building::Building(const std::string& name, const BuildingList& construct) {
	this->name=name;
}

std::string& Building::getName() {
	return name;
}

bool Building::Build(std::vector<std::vector<int>>& Intmap, int xBoundry, int yBoundry) {

	setPosition(sf::Vector2f(rand() % (xBoundry - 2), rand() % (yBoundry - 2)));
	unsigned int xMap = getPosition().x;
	unsigned int yMap = getPosition().y;
	unsigned int X2;
	unsigned int Y2;
	int xSize = getShape().getSize().x/10 ;
	int ySize = getShape().getSize().y / 10 ;
	for (int y = 0; y < yBoundry - ySize; y++)
	{
		for (int x = 0; x < xBoundry - xSize; x++)
		{
			//to ensure that it's always in the map
			X2 = ((xMap + x) % (xBoundry - xSize)) + 1;
			Y2 = ((yMap + y) % (yBoundry - ySize)) + 1;
			//basic check
			if (X2 > 0 && X2 + xSize < xBoundry && Y2 > 0 && Y2 + ySize < yBoundry && // just chechikng for boundry if % doesn't work
				Intmap[X2][Y2] < 2 && Intmap[X2 + xSize-1][Y2] < 2 && // max left building check
				Intmap[X2][Y2 + ySize-1] < PavementTile && Intmap[X2 + xSize-1][Y2 + ySize-1] < PavementTile && (//max right building check
					//"expert" checks
					(xSize>3? (Intmap[X2+3][Y2] < PavementTile && Intmap[X2 + 3][Y2+ ySize - 1] < PavementTile) : true) &&// middle top and middle bottom check
					(ySize > 3 ? (Intmap[X2 ][Y2+3] < PavementTile && Intmap[X2 + xSize - 1][Y2 + 3] < PavementTile) : true) && //middle left and middle right check  //  now everybode hates me for this as they should but it works lol
					//final check for walkable surface
					Intmap[X2 - 1][Y2 - 1] == PavementTile || Intmap[X2 + 1][Y2 + 1] == PavementTile)) { // looking in corners for PavementTile

				for (int i = 0; i < xSize; ++i) {
					for (int j = 0; j < ySize; ++j) {
						Intmap[X2 + i][Y2 + j] = getTile();
					}
				}				
				std::cout << "\nXmap" << xMap << " ,Ymap " << yMap
						  << "\nX2:" << X2 << " ,Y2:" << Y2;

				// i know i'ts confusing but just resources/Vector_shenanigens.png open for explenation
				setPosition( sf::Vector2f(Y2 * 10, X2 * 10)); 
				return true;


			}


		}

	}
	
	return false;
}