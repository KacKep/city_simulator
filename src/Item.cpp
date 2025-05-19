#include "Item.hpp"

Item::Item() 
	:name("error"),attack(0),swiftness(0)
{
	switch (rand() % 5)
	{
		case 0: {
			attack = 7;
			swiftness = 0;
			name = "baseball bat";
			break;
		}
		case 1: {
			attack = 2;
			swiftness = 40;
			name = "rock";
			break;
		}
		case 2: {
			attack = 5;
			swiftness = 20;
			name = "scissors";
			break;
		}
		case 3: {
			attack = 0;
			swiftness = 50;
			name = "boots";
			break;
		}
		case 4: {
				
			attack = 0;
			swiftness = 0;
			name = "indomitable human spirit";
			break;

		}
	}
	
}
	Item::~Item(){}


	int Item::getSwiftness() const{
		return swiftness;
	}
	int Item::getAttack1() const {
		return attack;
	}