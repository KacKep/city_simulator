#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Human.hpp"
#include "TileMap.hpp"
#include "Building.hpp"
#include "Shop.hpp"
#include "Hospital.hpp"
#include "OfficeBuilding.hpp"
#include <iostream>
#include "Entity.hpp"
#include "Human2.hpp"

bool operator== (Entity&  entity, Building& building);

class City 
{
public:
	City();
	~City();
	void start();
private:

	sf::Texture giveTexture(std::string path);

	void cross(int* level, int width, int height);



	long unsigned int numHumans;
	long unsigned int numBuildings;
	long unsigned int height;
	long unsigned int length;
	bool ValueSwitch2;
	bool ValueSwitch;
};

//getMap:



