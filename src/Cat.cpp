#include "Cat.hpp"
/**@File Animal created to show it living with an owner but not chasing it like a dog
*aCan walk on buildings
*/

sf::Texture Cat::texture(std::string(RESOURCE_DIR) + "/Cat.png");

Cat::Cat(Human* owner)
	:Animal(owner)
{

	setTexture(&texture);
	setSwiftness(50);
	setName("Cat");
}

//cats move independendly not caring about their owners. They move from one grass/flower tile to another and if they get hungry they hunt for food
void Cat::behavior() {
	//	//what happens when the cat gets to their desired target
	if (getTarget() == getPosition())
	{
		//if the hunger is 0, the animal starts to take damage
		if (getHunger() <= 0)
		{
			addHunger(0);
			addHealth(-2);
		}
		else
		{
			//if the animal isnt staving, the hunger decreases as well as happiness
			addHunger(-5);
			addHappiness(-1);
		}
		//making sure health doesnt exceed 100
		if (getHealth()>100)
		{
			addHealth(100 - getHealth());
		}


		if (rand()%2==0)
		{
			setTargetTile(FlowersTile);

		}
		else {
			setTargetTile(GrassTile);
		}
		hunt();

		
		chooseTarget();
	}

	walkBasic();
}