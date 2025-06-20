#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Human.hpp"
#include "TileMap.hpp"
#include "Shop.hpp"
#include "Hospital.hpp"
#include "OfficeBuilding.hpp"
#include "LiqourShop.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "Polytechnic.hpp"

///main primary class where basically everything happens

class City 
{
public:
	City();
	~City();


	void start();
private:
	//----Methods-----
	sf::Texture giveTexture(std::string path);

	void cross(int* level, int width, int height);

	void interactionBuilding();

	void interactionHumanBuilding(Entity& entity, Building& building);

	void createBuildings(std::vector<std::vector<int>>& Intmap );

	void createEntities();

	void interactionEntities();

	void camera(sf::RenderWindow& window, sf::View& view);

	void drawScreen(sf::RenderWindow& window, sf::View& view);
	///saving data from the entire simulation to a csv output file
	void save(std::vector<std::vector<int>>& Intmap);
	//-----------Variables-------

	std::vector<std::unique_ptr<Building>> buildings;
	std::vector<std::unique_ptr<Entity>> entities;
	///those following variables are inputted from an input file
	long unsigned int numHumans;
	long unsigned int numBuildings;
	long unsigned int maxIterations;
	long unsigned int height;
	long unsigned int length;
	float seed;
	
	//std::vector<std::vector<int>> Intmap;

	bool ValueSwitch2;
	bool ValueSwitch;

	std::string outputfile;
};

//getMap: