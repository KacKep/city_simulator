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

void Cat::behavior() {
	if (getTarget() == getPosition())
	{
		if (getHunger() <= 0)
		{
			addHunger(0);
			addHealth(-2);
		}
		else
		{
			addHunger(-5);
		}
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