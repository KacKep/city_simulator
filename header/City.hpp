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
#include "Animal.hpp"



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

	void interactionHumanBuilding(Entity& entity, Building& building);

	void createBuildings(std::vector<std::vector<int>>& Intmap );

	void createEntities();

	void interactionEntities();

	void camera(sf::RenderWindow& window, sf::View& view);
	//_----------Variables-------

	std::vector<std::unique_ptr<Building>> buildings;
	std::vector<std::unique_ptr<Entity>> entities;
	long unsigned int numHumans;
	long unsigned int numBuildings;
	long unsigned int height;
	long unsigned int length;
	
	//std::vector<std::vector<int>> Intmap;

	bool ValueSwitch2;
	bool ValueSwitch;
};

//getMap: