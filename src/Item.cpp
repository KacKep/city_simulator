#include "Item.hpp"

Item::Item() 
	:name("error"),
	attack(0),
	defence(0),
	swiftness(0)
{
	switch (rand() % 10)
	{
		case 0: {
			attack = 7;
			defence = 0;
			swiftness = 0;
			name = "Baseball Bat";
			break;
		}
		case 1: {
			attack = 2;
			defence = 0;
			swiftness = 40;
			name = "Rock";
			break;
		}
		case 2: {
			attack = 5;
			defence = 0;
			swiftness = 20;
			name = "Scissors";
			break;
		}
		case 3: {
			attack = 0;
			defence = 1;
			swiftness = 50;
			name = "Boots";
			break;
		}
		case 4: {
			attack = 6;
			defence = 0;
			swiftness = 35;
			name = "Knife";
			break;
		}
		case 5: {
			attack = 1;
			defence = 0;
			swiftness = 45;
			name = "Sharp Pencil";
			break;
		}
		case 6: {
			attack = 2;
			defence = 0;
			swiftness = 30;
			name = "Glass Bottle";
			break;
		}
		case 7: {
			attack = 1;
			defence = 2;
			swiftness = 10;
			name = "Riot Shield";
			break;
		}
		case 8: {
			attack = 0;
			defence = 3;
			swiftness = 0;
			name = "Aluminium Armor";
			break;
		}
		case 9: {
			attack = 0;
			defence = 0;
			swiftness = 0;
			name = "Indomitable Human Spirit";
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
	std:: string Item::getName() const {
	return name;
}