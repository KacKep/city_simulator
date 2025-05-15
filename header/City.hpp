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
	void background(sf::RenderWindow& window, int seed);
	void cross(int* level, int width, int height);

	std::vector<std::vector<int>> Intmap;
};

//getMap:



